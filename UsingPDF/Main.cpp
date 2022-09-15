#include <iostream>
#include <exception>
#include <sstream>
#include <iomanip>
#include <string>
#include <hpdf.h>
#include <string.h>
#include <istream>

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

int32_t main(int32_t argc, const char *argv[])
{
  PdfUserData pdf_user_data{"Creación del PDF "};
  HPDF_Doc pdf = HPDF_NewEx(HaruPdfErrorHandler, nullptr, nullptr, 0, &pdf_user_data);

  try
  {
    // std::istringstream file_name(argv[0]);
    // std::ifstream input_file(file_name.rdbuf());

    // Crear fuente para el pdf
    pdf_user_data = PdfUserData{"Creando fuente del PDF..."};
    HPDF_Font pdf_font = HPDF_GetFont(pdf, "Helvetica", NULL);

    pdf_user_data = PdfUserData{"Agregando una página..."};
    HPDF_Page page1 = HPDF_AddPage(pdf);
    HPDF_Page_SetWidth(page1, 400);
    HPDF_Page_SetHeight(page1, 500);

    // Y-axis is inverted

    pdf_user_data = PdfUserData{"Iniciando texto..."};
    HPDF_Page_BeginText(page1);

    // Write to the PDF
    HPDF_Page_SetFontAndSize(page1, pdf_font, 20);
    HPDF_Page_MoveTextPos(page1, 20, 450);
    HPDF_Page_ShowText(page1, "C++ Document PDF");
    HPDF_Page_EndText(page1);

    pdf_user_data = PdfUserData{"Guardando pdf..."};
    HPDF_SaveToFile(pdf, "Test.pdf");
    HPDF_Free(pdf);
  }
  catch (const PdfExeption &e)
  {
    HPDF_Free(pdf);
    std::cerr << e.what() << '\n';
  }
}