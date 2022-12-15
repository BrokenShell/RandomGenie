from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize


extensions = [
    Extension(
        "random_genie",
        ["engine.pyx"],
        extra_compile_args=["-std=c++14"],
        language="c++",
    ),
]

setup(
    name="random_genie",
    ext_modules=cythonize(extensions),
)
