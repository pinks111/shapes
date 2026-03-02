ЭВМ 2 семестр проект

Распределение обязанностей:
class Matrix:
	Matrix(size_t r, size_t c); - 
  
	~Matrix(); - 
  
	bool Get(size_t r, size_t c); - 
  
	void Set(size_t r, size_t c, bool state); - 

class Bitmap :
	Bitmap(size_t r, size_t c); - 
  
	Bitmap(const char* filename); - Муратов Влад

	~Bitmap(); - 

	bool Get(size_t r, size_t c); - 

	void Set(size_t r, size_t c, bool state); - 

	void Save(const char* filename); - 
