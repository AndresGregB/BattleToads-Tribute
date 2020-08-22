INC := `sdl2-config --cflags`
INC += -I.

LIB := `sdl2-config --libs`
LIB += -lSDL2 -lSDL2_image -lSDL2_mixer 

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
	docker run -v `pwd`:/home/docker -ti sdl-compiler make compile

docker-run:
	docker run --net host \
	-e DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix:ro \
	-v /run/user/`id -u`/pulse:/run/user/1000/pulse \
	-v `pwd`:/home/docker \
	sdl-compiler \
	make run

docker-run-mac:
	docker run --net host \
	-e DISPLAY=docker.for.mac.host.internal:0 \
	-v `pwd`:/home/docker \
	-v /run/user/`id -u`/pulse:/run/user/1000/pulse \
	sdl-compiler \
	make run
