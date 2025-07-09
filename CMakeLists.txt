cmake_minimum_required(VERSION 3.5)

include(CMakePrintHelpers)  #cmake_print_variable   fonksiyonu için
#proje ismi ayarlanıyor.
string(FIND ${CMAKE_CURRENT_SOURCE_DIR} / BaslangicIndeks REVERSE)
math(EXPR BaslangicIndeks "${BaslangicIndeks}+1")
string(SUBSTRING ${CMAKE_CURRENT_SOURCE_DIR} ${BaslangicIndeks} -1 ProjeIsmi)

#proje ismi belirleniyor
project(${ProjeIsmi})

#proje klasörünün yolu yeni bir değişkene atanıyor
set(Project_Dir ${CMAKE_SOURCE_DIR})

set(Kutuphane_Dir ${Project_Dir}/../../Kutuphaneler)

#inlcude ve src klasör yollarıda yeni bir değişkene atanıyor
set(Project_Include_Dir ${Project_Dir}/include)

set(Project_Src_Dir ${Project_Dir}/src)

#Kaynak Dosyalari ekleniyor
set(Project_Source_Files 
            ${Project_Src_Dir}/main.cpp
            ${Project_Src_Dir}/glad.c
            ${Project_Src_Dir}/shaderprogram.cpp
            ${Project_Src_Dir}/vertexbuffer.cpp       
            ${Project_Src_Dir}/vertexarrayobject.cpp        
            ${Project_Src_Dir}/GLWindow.cpp       
            ${Project_Src_Dir}/texturemanager.cpp      
            ${Project_Src_Dir}/indexbuffer.cpp        
            ${Project_Src_Dir}/shapecreator.cpp                                    
    )

include_directories(
    ${Project_Include_Dir}
    ${Kutuphane_Dir}/glm
    ${Kutuphane_Dir}
    )



set(glfw3_DIR ${Kutuphane_Dir}/glfw/lib/cmake/glfw3/)

find_package(glfw3 3.4 REQUIRED)

add_executable(${PROJECT_NAME} ${Project_Source_Files})

target_link_libraries(${PROJECT_NAME} glfw)