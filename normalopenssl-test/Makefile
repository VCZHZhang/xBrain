#g++ ssl_server.cpp -o myserver  -lssl -lcrypto
#g++ ssl_client.cpp -o myclient -lssl -crypto
#g++ ssl_server.cpp -o myserver -Wl,-Bstatic -L/home/dengjunxing/mygithub/gm-out/lib -lssl -Wl,-rpath -L/home/dengjunxing/mygithub/gm-out/lib -L/home/dengjunxing/mygithub/gm-out/lib  -lcrypto -Wl,-rpath -L/home/dengjunxing/mygithub/gm-out/lib
#gcc ssl_server.c -o myserver -I  /home/dengjunxing/mygithub/gm-out/include  -L/home/dengjunxing/mygithub/gm-out/lib -lgmssl  -lgmcrypto 
gcc ssl_server.c -o myserver -I  /home/dengjunxing/mygithub/gm-out/include  -L./ -l:libgmssl.a  -l:libgmcrypto.a

gcc ssl_client.c -o myclient -I  /home/dengjunxing/mygithub/gm-out/include  -Wl,-Bstatic -L/home/dengjunxing/mygithub/gm-out/lib -lgmssl  -Wl,-Bstatic -L/home/dengjunxing/mygithub/gm-out/lib -lgmcrypto 
