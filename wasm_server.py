import socketserver
import http.server
import os
import argparse

if __name__ == "__main__":
    # parse arguments
    parser = argparse.ArgumentParser(
                        prog='Wasm Server',
                        description='Wasm Server host on a given directory',
                        epilog='Text at the bottom of help')
    parser.add_argument('dir')           # positional argument
    parser.add_argument('-p', '--port', default=8080)      # option that takes a value
    parser.add_argument('-o', '--overwrite', action='store_true', default=False)      # option that takes a value
    args = parser.parse_args()

    target_dir = os.path.abspath(args.dir)
    port = int(args.port)


    # copy index.html and redirect .js file
    if not os.path.exists(os.path.join(target_dir, 'index.html')) or args.overwrite:
        with open('data/index.html', 'r') as f:
            with open(os.path.join(target_dir, 'index.html'), 'w') as g:
                # find file name with .html extension
                html_file = [f for f in os.listdir(target_dir) if f.endswith('.html') and not f.startswith("index.")][0]
                js_script = html_file.replace('.html', '.js')
                html_content = f.read().replace('{{js_script}}', js_script)
                g.write(html_content)
        print('index.html copied to target directory')


    class Handler(http.server.SimpleHTTPRequestHandler):
        def __init__(self, *args, **kwargs):
            super().__init__(*args, directory=target_dir, **kwargs)

    socketserver.TCPServer.allow_reuse_address = True
    with socketserver.TCPServer(("", port), Handler) as httpd:
        print("serving at directory", target_dir)
        print("serving at url", f'http://localhost:{port}')
        httpd.serve_forever()