# sc3010

# Compile on windows
gcc client.c -o client -lws2_32
gcc server_vuln.c -o server_vuln -lws2_32
gcc server_fixed.c -o server_fixed -lws2_32