INC := `sdl2-config --cflags`
INC += -I.

LIB := `sdl2-config --libs`
LIB += -lSDL2 -lSDL2_image -lSDL2_mixer 

CC := g++
CFLAGS := 

UNAME := $(shell uname)

ifeq ($(UNAME),Darvin)
	CC=clang++
else
	CC=g++
endif

clean:
	rm -rf .config && \
	cd BattleToads && \
	rm -f *.o *~ Main

compile:
	cd BattleToads && \
	$(CC) $(CFLAGS) -g *.cpp $(INC) $(LIB) -o Main 	

run:
	cd BattleToads && \
	./Main 	

dep:
	sudo apt install -y libsdl2-dev libsdl2-mixer-dev libsdl2-image-dev

format:
	find BattleToads -name '*.cpp' -exec indent {} \;
	find BattleToads -name '*.h' -exec indent {} \;

docker-build:
	docker build . -t sdl-compiler

docker-compile:	docker-build
	docker run -v $(PWD):/home/docker -ti sdl-compiler make compile

docker-run:
	docker run --net host \
	-e DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix:ro \
	--volume=/run/user/1000/pulse:/run/user/1000/pulse \
	-v "$(PWD):/home/docker" \
	sdl-compiler \
	make run

docker-mac-run:
	docker run --net host -e DISPLAY=docker.for.mac.host.internal:0 \
	-v "$(PWD):/home/docker" \
	sdl-compiler \
	$(args)
