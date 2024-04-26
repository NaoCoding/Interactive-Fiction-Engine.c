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
            cmd = self.path.split("/")
            self.end_headers()
            
            if "start_game_html" in cmd[-1]:
                out = check_output(["./api","html",cmd[-1][len("start_game_html"):]])
                file = open("./output/" + out.decode(),"rb" ).read()
                self.wfile.write(file)
            
            elif "start_game_js" in cmd[-1]:
                out = check_output(["./api","js",cmd[-1][len("start_game_js"):]])
                file = open("./output/" + out.decode() ,"rb").read()
                self.wfile.write(file)
            
            


        
        




server = HTTPServer(host,Server)
print("Server started at" + str(server.server_address))
server.serve_forever()