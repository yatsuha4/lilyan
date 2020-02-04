/***********************************************************************//**
	@file
***************************************************************************/
#pragma once
/***********************************************************************//**
	@brief 
***************************************************************************/
class sample
  : public lilyan::Parser
{
 public:
  sample() = default;
  ~sample() = default;

  std::any main(Buffer& buffer) {
    {
      Semantic semantic;
      Buffer _buffer(buffer);
      if(semantic.append(expr(_buffer))) {
        buffer = _buffer;
        return onMainExpr(semantic[1]);
      }
    }
    return std::any();
  }

  std::any expr(Buffer& buffer) {
    {
      Semantic semantic;
      if(semantic.append(term())) {
        return onExpr(1);
      }
    }
    {
      Semantic semantic;
      if(semantic.append(expr()) && 
         semantic.append(buffer.match(std::regex(R"^\s(+)"))) && 
         semantic.append(term())) {
        return onAdd(semantic[1], semantic[3]);
      }
    }
    {
      Semantic semantic;
      if(semantic.append(expr()) &&
         semantic.append(buffer.match(std::regex(R"\s(-)"))) && 
         semantic.append(term())) {
        return onSub(semantic[1], semantic[3]);
      }
    }
    return std::any();
  }

 protected:
  virtual std::any onMainExpr(const std::any& v1) = 0;
  virtual std::any onExpr(const std::any& v1) = 0;
  virtual std::any onAdd(const std::any& v1, const std::any& v3) = 0;
};
/***********************************************************************//**
	$Id$
***************************************************************************/
