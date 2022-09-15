#include <iostream>
#include <exception>
#include <sstream>
#include <iomanip>
#include <string>
#include <hpdf.h>

struct PdfUserData
{
  std::string Message;
};
class PdfExeption : public std::exception
{
  public:

    PdfExeption(const HPDF_UINT error_no, const HPDF_UINT detail_no, PdfUserData* const user_data = nullptr)
      : ErrorNo{ error_no }
      , DetailNo{ detail_no }
      , UserData{ user_data }
      {
      }

    virtual const char* what() const noexcept
    {
      std::ostringstream out;
      out << "Error number: " << std::hex << this->ErrorNo
          << ", Detail Number: " << std::hex << this->DetailNo;

      if (UserData != nullptr)
      {
        out << ", Error Message: " << this->UserData->Message;
      }

      return out.str().c_str();
    }

  private:
    HPDF_UINT ErrorNo;
    HPDF_UINT DetailNo;
    PdfUserData* UserData;
};

[[noreturn]] void HaruPdfErrorHandler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void* user_data)
{
  throw PdfExeption(static_cast<HPDF_UINT>(error_no),
                    static_cast<HPDF_UINT>(detail_no),
                    static_cast<PdfUserData*>(user_data));
}

int32_t main()
{
  try
  {
    HPDF_Doc pdf = HPDF_New(HaruPdfErrorHandler, nullptr);
  }
  catch(const PdfExeption& e)
  {
    std::cerr << e.what() << '\n';
  }
}