#include <iostream>
#include <exception>
#include <sstream>
#include <iomanip>
#include <string>
#include <hpdf.h>
#include <string.h>
#include <fstream>

struct PdfUserData
{
  std::string Message;
};
class PdfExeption : public std::exception
{
public:
  PdfExeption(const HPDF_UINT error_no, const HPDF_UINT detail_no, PdfUserData *const user_data = nullptr)
      : ErrorNo{error_no}, DetailNo{detail_no}, UserData{user_data}
  {
  }

  virtual const char *what() const noexcept
  {
    sprintf(this->Buffer, "Error number: %u, Detail number: %u", this->ErrorNo, this->DetailNo);

    if (UserData != nullptr)
    {
      auto prev_text = strdup(this->Buffer);
      sprintf(this->Buffer, "%s, Error message: %s.", prev_text, this->UserData->Message.c_str());
      free(prev_text);
    }
    return this->Buffer;
  }

private:
  HPDF_UINT ErrorNo;
  HPDF_UINT DetailNo;
  PdfUserData *UserData;
  mutable char Buffer[2048]; // Se puede modificar aunque el método sea const
};

[[noreturn]] void HaruPdfErrorHandler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data)
{
  throw PdfExeption(static_cast<HPDF_UINT>(error_no),
                    static_cast<HPDF_UINT>(detail_no),
                    static_cast<PdfUserData *>(user_data));
}

int32_t main(int32_t argc, char *argv[])
{
  if (argc < 2)
  {
    std::cerr << "At least one argument is required.\n";
    return EXIT_FAILURE;
  }

  PdfUserData pdf_user_data{"Creación del PDF "};
  HPDF_Doc pdf = HPDF_NewEx(HaruPdfErrorHandler, nullptr, nullptr, 0, &pdf_user_data);
  HPDF_REAL doc_height;
  HPDF_REAL doc_width;
  int32_t lines_number = 0;
  int32_t font_size = 12;

  try
  {
    std::ifstream input_file{argv[1]};
    pdf_user_data = PdfUserData{"Creating font..."};
    HPDF_Font pdf_font = HPDF_GetFont(pdf, "Helvetica", NULL);

    while (!input_file.is_open())
    {
      std::cerr << "Error when trying to open file.\n";
      return EXIT_FAILURE;
    }

    // Read lines of file
    while (!input_file.eof())
    {
      std::string line;
      getline(input_file, line);
      lines_number++;
    }

    pdf_user_data = PdfUserData{"Adding one page..."};
    HPDF_Page page1 = HPDF_AddPage(pdf);
    doc_height = HPDF_Page_GetHeight(page1) + lines_number * font_size;
    doc_width = HPDF_Page_GetWidth(page1);

    HPDF_Page_SetWidth(page1, doc_width);
    HPDF_Page_SetHeight(page1, doc_height);

    pdf_user_data = PdfUserData{"Starting text..."};

    HPDF_Page_BeginText(page1);
    HPDF_Page_SetFontAndSize(page1, pdf_font, font_size);
    HPDF_Page_MoveTextPos(page1, 0, doc_height - 10);

    // Return cursor pointer to the beginning of the file.
    input_file.seekg(0, std::ios::beg);

    while (!input_file.eof())
    {
      std::string output_text;
      getline(input_file, output_text);
      HPDF_Page_ShowText(page1, output_text.c_str());
      HPDF_Page_MoveTextPos(page1, 0, -18);
    }

    HPDF_Page_EndText(page1);

    pdf_user_data = PdfUserData{"Saving PDF..."};
    HPDF_SaveToFile(pdf, "Out.pdf");
    HPDF_Free(pdf);
  }
  catch (const PdfExeption &e)
  {
    HPDF_Free(pdf);
    std::cerr << e.what() << '\n';
  }
}