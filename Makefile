PROJECT   =    face_quality

RES 	  :=	main.o

LDFLAGS += -lopencv_core -lopencv_imgcodecs -lpthread -ldpfacequality -lboost_filesystem -lboost_system

LDFLAGS   += -L$(STAGING_DIR)/usr/lib

CUR_DIR   =   $(shell pwd)
SRC       =   $(CUR_DIR)/src
BUILD     =   $(CUR_DIR)/build
VPATH     =   $(SRC)


.PHONY: all clean

all: $(BUILD) $(PROJECT)

$(PROJECT): $(RES) $(OBJ)
	$(CXX) $(CFLAGS) $(addprefix $(BUILD)/, $^) -o $@ $(LDFLAGS)

%.o : %.cpp
	$(CXX) -c $(CFLAGS) $< -o $(BUILD)/$@

clean:
	$(RM) -rf $(BUILD)
	$(RM) $(PROJECT)

$(BUILD) :
	-mkdir -p $@
