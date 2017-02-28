## Make 最低版本号要求
cmake_minimum_required (VERSION 2.8)
## 项目信息
project (mmloop)
include(${PROJECT_SOURCE_DIR}/../mmloop.cmake)
message("source: " ${TOP_SRC})
include_directories(${TOP_SRC}/../libuv/include
	${TOP_SRC}/../libuv/src
	${TOP_SRC}/../libuv/src/win
	${TOP_SRC}/../libuv/src/unix)

link_directories(${TOP_SRC}/../libuv/Release)
message("link dir" ${LINK_DIR})
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
	message("this operation platform is linux/unix")
	# 查找当前目录下的所有源文件
	# 并将名称保存到 DIR_SRCS 变量
	aux_source_directory(./  DIR_SRCS)
	# 指定生成目标
	# add_executable(Imager main.cpp src/DPer/BmpPer.cpp)
	add_library (mmloop STATIC ${DIR_SRCS})
	# 添加本工程链接库依赖
	target_link_libraries(mmloop uv)
else()
	message("this operation platform is windows")
	# 查找src目录下的所有源文件
	# 并将名称保存到 DIR_SRCS 变量
	aux_source_directory(./  DIR_SRCS)
	# 指定生成目标
	# add_executable(Imager main.cpp ${DIR_SRCS})
	# 生成动态链接库
	add_library (mmloop STATIC ${DIR_SRCS})
	# 添加本工程链接库依赖
	target_link_libraries(mmloop uv)
endif()
