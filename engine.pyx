cdef extern from "engine.hpp":
    cdef cppclass RandomNumberEngine:
        RandomNumberEngine() except +
        int generateInt(int min, int max)
        double generateDouble(double min, double max)


cdef class PyRandomNumberEngine:
    cdef RandomNumberEngine engine

    def __cinit__(self):
        self.engine = RandomNumberEngine()

    cpdef generate_int(self, int min, int max):
        return self.engine.generateInt(min, max)

    cpdef generate_double(self, double min, double max):
        return self.engine.generateDouble(min, max)
