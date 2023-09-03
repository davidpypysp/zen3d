
import subprocess
import argparse
import json as json
import logging
from typing import List

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger("debug.py")

DEBUG_FOLDER = 'bazel-debug'
LAUNCH_JSON_PATH = '.vscode/launch.json'

def build_debug_target(target: str):
    return subprocess.call(['bazel', '--output_base=' + DEBUG_FOLDER, 'build', target, '--compilation_mode=dbg', '--verbose_failures'])

def get_target_path(target: str):
    return target.replace('//', '').replace(':', '/')

def generate_debug_config(target: str):
     return {
        "name": "//zen/demo:gltf_model_loader_demo",
        "type": "cppdbg",
        "request": "launch",
        "program": "${workspaceFolder}/" + DEBUG_FOLDER + "/execroot/zen/bazel-out/k8-dbg/bin/" + get_target_path(target),
        "args": [],
        "stopAtEntry": True,
        "cwd": "${workspaceFolder}",
        "environment": [],
        "externalConsole": False,
        "MIMode": "gdb",
        "setupCommands": [
            {
                "description": "Enable pretty-printing for gdb",
                "text": "-enable-pretty-printing",
                "ignoreFailures": True
            }
        ]
     }

def write_launch_json(config):
    launch_json = {}
    with open(LAUNCH_JSON_PATH, 'r') as f:
        launch_json = json.load(f)
    with open(LAUNCH_JSON_PATH, 'w') as f:
        if 'configurations' not in launch_json:
            launch_json['configurations'] = []

        configs: List = launch_json['configurations']
        for launch_config in configs:
            if launch_config['name'] == config['name']:
                print('overwriting existing config: ' + config['name'])
                configs.remove(launch_config)
        configs.append(config)
        f.write(json.dumps(launch_json, indent=4))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
                        prog='debug_bazel_target',
                        description='generate bazel target debug config in .vscode/launch.json',
                        epilog='Text at the bottom of help')
    parser.add_argument('target')           # positional argument
    args = parser.parse_args()

    logger.info("building target: " + args.target)
    signal = build_debug_target(args.target)
    if signal != 0:
        logger.error('build target failed: ' + args.target)
        exit(1)

    logger.info('build success')
    config = generate_debug_config(args.target)
    write_launch_json(config)
    logger.info('debug target generated in ' + LAUNCH_JSON_PATH + ': ' + args.target)







