import sys
import http.server
from http.server import BaseHTTPRequestHandler,HTTPServer

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
            self.send_response(200)
            file = open("." + self.path,"rb").read()
            self.end_headers()
            self.wfile.write(file)

        else:
            self.send_response(200)
            cmd = self.path.split("/")
            self.end_headers()
            if "start_game_html" in cmd[-1]:
                file = open("./output/scene" + cmd[-1].split('_')[-1] + ".html","rb" ).read()
                self.wfile.write(file)
            
            elif "start_game_js" in cmd[-1]:
                file = open("./output/scene" + cmd[-1].split('_')[-1] + ".js" ,"rb").read()
                self.wfile.write(file)
            
            


        
        




server = HTTPServer(host,Server)

server.serve_forever()