# Sea-battle task specific CMakeLists.txt

set(HEADER_FILES
        ship.h)

set(STUB_SOURCE_FILES
        stub.cc)

add_executable(sea-battle ${HEADER_FILES} ${STUB_SOURCE_FILES})