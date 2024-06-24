add_executable(client client.c
)
message(STATUS "${Green} client is loaded ${ColourReset}")

add_executable(server server.c)
message(STATUS "${Green} server is loaded ${ColourReset}")
