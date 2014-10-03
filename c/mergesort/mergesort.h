#define TESTMACRO(array)			\
	({					\
	typeof(array) *__tmp = &array;		\
	})
