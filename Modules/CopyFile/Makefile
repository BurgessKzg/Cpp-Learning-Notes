srcs := $(shell ls *.cpp)
objs := $(patsubst %.cpp,%.o,$(srcs))
#BUILD_MAP := build_map
#LOCAL_LDFLAGS += -Werror -std=c++11 -D _GLIBCXX_USE_CXX11_ABI=0
LOCAL_LDFLAGS += -Werror -std=c++11 -D PRINTF_INFORMATION
#LOCAL_LDFLAGS += -Werror -std=c++11 

CopyFile: $(objs)
	g++ -o $@ $^ $(LOCAL_LDFLAGS)

%.o:%.cpp
	g++ -c -o $@ $< $(LOCAL_LDFLAGS)

clean:
	rm -f CopyFile *.o

