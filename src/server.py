import sys
import http.server
from http.server import BaseHTTPRequestHandler,HTTPServer
from subprocess import check_output

host = ("localhost",8000)
downloaded = []

class Server(BaseHTTPRequestHandler):

    def do_GET(self):
        
        if self.path == '/':
            self.send_response(200)
            html = open("index.html").read()
            self.end_headers()
            self.wfile.write(bytes(html , 'utf-8'))
        
        elif "command" not in self.path:
            if self.path != "/favicon.ico":
            
                self.send_response(200)
                file = open("." + self.path,"rb").read()
                self.end_headers()
                self.wfile.write(file)

        else:
            self.send_response(200)
            cmd = self.path.split("/")[-1]
            self.end_headers()
            
            if "new?game" in cmd:
                cmd = cmd.split("?")
                out = check_output(["./api","new_game",cmd[-1]])
                if(cmd[-1] == "createFile"):
                    self.wfile.write(out)
                else:
                    file = open("./output/" + out.decode(),"rb" ).read()
                    self.wfile.write(file)
            
            elif "start?game" in cmd:
                cmd = cmd.split("?")
                out = check_output(["./api","change_scene",cmd[-2],cmd[-1]])
                file = open("./output/" + out.decode(),"rb" ).read()
                self.wfile.write(file)
            
            elif "sub?game" in cmd:
                cmd = cmd.split("?")
                out = check_output(["./api","change_subscene",cmd[-2],cmd[-1]])
                file = open("./output/" + out.decode(),"rb" ).read()
                self.wfile.write(file)
            elif "close?subgame" in cmd:
                cmd = cmd.split("?")
                out = check_output(["./api","closesubscene",cmd[-2],cmd[-1]])
                file = open("./output/" + out.decode(),"rb" ).read()
                self.wfile.write(file)
            elif "save?" in cmd:
                cmd = cmd.split("?")
                out = check_output(["./api","save",cmd[-3],cmd[-2],cmd[-1]])


server = HTTPServer(host,Server)
print("Server started at" + str(server.server_address))
server.serve_forever()