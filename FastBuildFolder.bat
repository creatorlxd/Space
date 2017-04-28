@echo off
set /p Name=
set h=%Name%.h
set cpp=%Name%.cpp
mkdir %Name%
cd %Name%
mkdir Include
cd Include
echo #pragma once > %h%
cd ..
mkdir Source
cd Source
echo #include "../Include/%h%" > %cpp%