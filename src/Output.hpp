/***********************************************************************//**
	@file
***************************************************************************/
#pragma once
/***********************************************************************//**
	@brief 
***************************************************************************/
class Output {
 private:
  static const size_t INDENT = 2;

 private:
  std::unique_ptr<std::ofstream> stream_;
  bool isNewline_;
  size_t indent_;

 public:
  Output();
  ~Output();

  bool open(const std::string& path);
  void close();

  Output& operator<<(char control);

  template <class T>
  Output& operator<<(const T& value) {
    indent();
    getStream() << value;
    return *this;
  }

  Output& enter();

 private:
  std::ostream& getStream() const;
  void indent();
};
