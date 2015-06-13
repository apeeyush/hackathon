import time
import BaseHTTPServer

HOST_NAME = 'localhost' # !!!REMEMBER TO CHANGE THIS!!!
PORT_NUMBER = 8080 # Maybe set this to 9000.


class MyHandler(BaseHTTPServer.BaseHTTPRequestHandler):
    def do_HEAD(s):
        s.send_response(200)
        s.send_header("Content-type", "text/html")
        s.end_headers()
    def do_GET(s):
        """Respond to a GET request."""
        if s.path == '/ping' or s.path == '/ping/':
            s.send_response(200)
            s.send_header("Content-Type", "application/json")
            s.end_headers()
            s.wfile.write({'ok':'true'})
        elif s.path == '/start' or s.path == '/start/':
            s.send_response(200)
            s.send_header("Content-Type", "application/json")
            s.end_headers()
            # If game initialized
            s.wfile.write({'ok':'true'})

        elif s.path == '/play' or s.path == '/play/':
            s.send_response(200)
            s.send_header("Content-Type", "application/json")
            s.end_headers()
        else:
            s.send_response(403)
            s.send_header('Content-Type', 'application/json')
            s.end_headers()

if __name__ == '__main__':
    server_class = BaseHTTPServer.HTTPServer
    httpd = server_class((HOST_NAME, PORT_NUMBER), MyHandler)
    print time.asctime(), "Server Starts - %s:%s" % (HOST_NAME, PORT_NUMBER)
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    httpd.server_close()
    print time.asctime(), "Server Stops - %s:%s" % (HOST_NAME, PORT_NUMBER)
