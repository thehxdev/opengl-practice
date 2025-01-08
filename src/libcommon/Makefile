include ../../config.mk

LIBCOMMON := $(LOCAL_LIB_DIR)/libcommon.a
LIBCOMMON_SRCS = gl.cpp common.cpp
LIBCOMMON_OBJS = $(LIBCOMMON_SRCS:.cpp=.o)

$(LIBCOMMON): $(LIBCOMMON_OBJS)
	ar rcs $(LIBCOMMON) $(LIBCOMMON_OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -rf *.o
