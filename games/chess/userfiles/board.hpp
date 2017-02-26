template <typename T>
int const board<T>::m_length = 8;

template <typename T>
board<T>::board()
{
  m_data = new T*[m_length];
  for(int i = 0; i < m_length; i++)
    m_data[i] = new T[m_length];
}

template <typename T>
board<T>::~board()
{
  if(m_data != nullptr)
  {
    for(int i = 0; i < m_length; i++)
      delete [] m_data[i];
    delete [] m_data;
    m_data = nullptr;
  }
}

template <typename T>
board<T>::board(const board<T> & rhs)
{
  for(int i = 0; i < m_length; i++)
    for(int j = 0; j < m_length; j++)
      m_data[i][j] = rhs.m_data[i][j];
}

template <typename T>
const board<T> & board<T>::operator = (const board<T> & rhs)
{
  for(int i = 0; i < m_length; i++)
    for(int j = 0; j < m_length; j++)
      m_data[i][j] = rhs.m_data[i][j];
  return *this;
}

template <typename T>
board<T>::board(board<T> && rhs)
{
  if(m_data != nullptr)
  {
    for(int i = 0; i < m_length; i++)
      delete [] m_data[i];
    delete [] m_data;
  }
  m_data = rhs.m_data;
  rhs.m_data = nullptr;
}

template <typename T>
const T* board<T>::operator [] (const int & i) const
{
  return m_data[i];
}

template <typename T>
T* board<T>::operator [] (const int & i)
{
  return m_data[i];
}