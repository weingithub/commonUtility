CCOMPILE = gcc
CPPCOMPILE = g++
COMPILEOPTION = -c -g -fPIC -D__USERWLOCK -D__TEMP_COPY_ #-D_FILE_OFFSET_BITS=64 #-D__TEST_VERSION
INCLUDEDIR = 
LIBDIRS =  
COMMONOBJS =  
SHAREDLIB =
SHARE_SO=
APPENDLIB = 
SRCS	=	$(wildcard *.cpp)
OBJS	=	$(patsubst %.cpp, %.o, $(SRCS))   
TARGET  = libutility.so

default:compile

compile: $(OBJS)
	$(CPPCOMPILE) $^ -g -shared -Wl,-soname -o $(TARGET)
.cpp.o: $(COMMONOBJS)
	$(CPPCOMPILE) -c -o $*.o $(COMPILEOPTION) $(INCLUDEDIR)  $*.cpp

	
.PHONY:clean
clean: 
	rm -f $(OBJS) $(TARGET)
	
	


	



	
	
