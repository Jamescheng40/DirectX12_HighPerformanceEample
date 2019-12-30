cmake_minimum_required( VERSION 3.16.1 ) # Latest version of CMake when this file was created.


set( HEADER_FILES
    inc/Dx12HPerfApp.h
    inc/CommonInc.h
    inc/Win64App.h
    inc/Dx12Helper.h
    inc/driver/DX12Resources.h
    inc/RenderBase.h
)

set( SHADER_FILES
    shaders/VertexShader.hlsl
    shaders/PixelShader.hlsl
)


set( SRC_FILES
    src/main.cpp
    src/Dx12HPerfApp.cpp
    src/Win64App.cpp
    src/driver/DX12Resources.cpp
    src/RenderBase.cpp
)

source_group( "Resources\\Shaders" FILES ${SHADER_FILES} )

set_source_files_properties( shaders/VertexShader.hlsl PROPERTIES 
    VS_SHADER_TYPE Vertex
    VS_SHADER_MODEL 5.1
)

set_source_files_properties( shaders/PixelShader.hlsl PROPERTIES 
    VS_SHADER_TYPE Pixel
    VS_SHADER_MODEL 5.1
)

add_executable( Dx12HPerfApp WIN32
    ${HEADER_FILES} 
    ${SRC_FILES}
    ${SHADER_FILES}
)

target_include_directories( Dx12HPerfApp
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_link_libraries( Dx12HPerfApp
    PUBLIC d3d12.lib
    PUBLIC D3DCompiler.lib
    PUBLIC Shlwapi.lib
    PUBLIC dxgi.lib
)