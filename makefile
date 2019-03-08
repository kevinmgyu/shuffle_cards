TARGET  := libshuffle_cards.a
INCS = -I ../../../network -I ../../../utils -I ../../../base -I ../../../fullnode/ -I ../../../httptools -I ../../sign_server/lib 
LIBS = -L ../../sign_server/lib -lsign_client -L ../../../fullnode -lfullnode  -L ../../../utils -lutils -L ../../../bitcoin -L ../../../network -lnetwork -L ../../../base -lbbtbase -L ../../../httptools -lhttptools -lrestclient-cpp -lcurl -L ../../../protobuf-3.5.0/lib -L ../../lib -lprotobuf -L /usr/local/lib/ -lleveldb -lrdkafka -lssl -lcrypto  -levent  -Wl,-Bstatic -lfc -lsecp256k1 -lev -ljansson -lmpdec -lmysqlclient -lz -lhiredis -lboost_system -lboost_thread -lboost_chrono -lboost_filesystem -lboost_date_time -lboost_context -lboost_coroutine -lboost_iostreams -Wl,-Bdynamic -lm -lpthread -ldl
include ../../../makefile.inc
$(TARGET) : $(OBJS)
	ar -rs $@ $^
