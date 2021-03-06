
#include "Response.h"
using namespace resthub;

#include <cassert>

using namespace std;

Response::Response(Request* req)
{
  m_req = req;
  // Claim ownership
  m_req->parent(this);
}

Response::Response(Response&& rhs)
{
  m_req = rhs.m_req;
  // Move ownership
  if(m_req->parent() == &rhs)
    m_req->parent(this);
}

Response::~Response()
{
  // Delete the request if we own it.
  if(m_req && m_req->parent() == this)
    delete m_req;
}

Response& Response::operator=(Response&& rhs)
{
  this->~Response();

  m_req = rhs.m_req;
  // Move ownership
  if(m_req->parent() == &rhs)
    m_req->parent(this);

  return *this;
}

string Response::error_str()
{
  if(!ok()) {
    return m_req->m_data_in.str();
  }
  return "";
}

string Response::str()
{
  assert(ok());
  return m_req->m_data_in.str();
}






