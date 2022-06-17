# 支持选项编译release 和 debug两个版本二进制文件输出
# 理论上能编译出所有变体，或指定变体
# 编译结果输出到临时目录
import sys
import argparse
import subprocess
import os

self_path = __file__
self_dir, self_fname = os.path.split(self_path)
engine_root = os.path.abspath(self_dir + "/../../")
print("engine_root:", engine_root)
builtin_shader_include_dir = os.path.join(engine_root, "assets", "builtin_shaders", "inc")
fxc_path = os.path.join(engine_root, "external", "dxc", "bin", "x64", "dxc.exe")

parser = argparse.ArgumentParser()
parser.add_argument("-P", "--path", help="folder path", type=str, default=engine_root, required=False)
comand_args = parser.parse_args()
print(comand_args.path)

def GetFiles(dir):
    rets = []
    for cdir,  dirs, files in os.walk(dir):
        for file in files:
            fname, fext = os.path.splitext(file)
            if fext == ".hlsl" :
                full_path = os.path.abspath(os.path.join(cdir, file))
                rets.append(full_path)

    return rets 

class DXCommandBuilder():
    options = []
    def __init__(self, path):
        self.fpath = path

    def AddOption(self, opt, arg):
        if opt == None or opt == "":
            return
        self.options.append(opt)
        if arg != None and arg != "":
            self.options.append(arg)

    def Execute(self):
        args = list(self.options)
        args.insert(0, fxc_path)
        args.append(self.fpath)
        command = " ".join(args)
        subprocess.Popen(command, shell = True)

    def Reset(self, path):
        self.fpath = path
        self.options = []


class ShaderHeadInfo():
    ps_entry = None
    vs_entry = None
    sm = "6_1"

    def SetShaderModel(self, main, other):
        self.sm = str(main) + "_" + str(other)


    def GetVSProfile(self):
        if self.vs_entry != None:
            return "vs_" + self.sm
        return None
    
    def GetPSProfile(self):
        if self.ps_entry != None:
            return "ps_" + sm
        return None


def ParseShaderHeader(path):
    if not os.path.exists(path):
        return ShaderHeadInfo()

    head_info = ShaderHeadInfo()
    begin_head = False
    for line in open(path):
        line_str = line.strip()
        if begin_head and line_str == "//ENDHEAD":
            break

        if not begin_head and line_str == "//HEAD":
            begin_head = True
        
        if begin_head and line_str.startswith("//"):
            line_str = line_str[2:].strip()
            args = line_str.split(':')
            if len(args) >= 2:
                if args[0].strip() == "VSEntry":
                    head_info.vs_entry = args[1].strip()
                elif args[0].strip() == "PSEntry":
                    head_info.ps_entry = args[1].strip()
                elif args[0].strip() == "SM":
                    vers = args[1].strip().split('.')
                    if len(vers) >= 2:
                        head_info.SetShaderModel(vers[0], vers[1])
        
    return head_info


# debug: dxc.exe -T 
def DoComplie():
    files = GetFiles(comand_args.path)
    builder = DXCommandBuilder("")
    for file in files:
        hinfo = ParseShaderHeader(file)
        # check vs
        vsp = hinfo.GetVSProfile()
        if vsp != None:
            dir_name, file_name = os.path.split(file)
            fname, ext = os.path.splitext(file_name)
            out_file_path = os.path.join(dir_name, fname + ".vs.cso")
            builder.Reset(file)
            builder.AddOption("-Fo", out_file_path)
            builder.AddOption("-T", vsp)
            builder.AddOption("-E", hinfo.vs_entry)
            builder.AddOption("-I", builtin_shader_include_dir)
            builder.AddOption("-I", ".")
            # debug info
            builder.AddOption("-Zi", "") # Enable debug infomation
            builder.AddOption("-Fd", os.path.join(dir_name, fname + ".vs.pdb"))
            builder.Execute()

DoComplie()