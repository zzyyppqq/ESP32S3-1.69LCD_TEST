import os, sys, time, re

os.chdir(os.path.dirname(os.path.abspath(__file__)))

image_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), '../images')
output_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), '../')
image_format = "true_color_alpha"
image_out_format = "C"

# 检测images下的文件名是否包含"img_src_"，没有的话则重命名添加"img_src_"
file_list = os.listdir(image_path)
print(file_list)

for file_name in file_list:
    if file_name.find("img_src_") == -1:
        os.rename(os.path.join(image_path, file_name), os.path.join(image_path, "img_src_" + file_name))
        os.system("python3 main.py -f %s -ff %s -o %s %s" % (image_format, image_out_format, output_path, os.path.join(image_path, "img_src_" + file_name)))
    else:
        os.system("python3 main.py -f %s -ff %s -o %s %s" % (image_format, image_out_format, output_path, os.path.join(image_path, file_name)))

# # 去除img_src_前缀及后缀
# file_list = os.listdir(image_path)
# add_image_list = []
# for file_name in file_list:
#     add_image_list.append(file_name.replace("img_src_", "").split(".")[0])
# print(add_image_list)

# # 读文件ResourcePool.cpp包含IMPORT_IMG(a)的a的值,并添加到一个列表中
# with open(os.path.join(output_path, "../ResourcePool.cpp"), "r") as f:
#     lines = f.readlines()
# f.close()

# now_image_list = []
# for line in lines:
#     # 使用正则表达式查找(IMPORT_IMG(a);),a为变量
#     if re.search(r'IMPORT_IMG\((\w+)\);', line):
#         # now_image_list.append(re.search(r'IMPORT_IMG\((\w+)\);', line).group(1))
#         now_image_list.append(line.split("(")[1].split(")")[0])
#         if line.split("(")[1].split(")")[0] in add_image_list:
#             add_image_list.remove(line.split("(")[1].split(")")[0])

# print(add_image_list)
# print(now_image_list)

# # 将add_image_list中的值添加到ResourcePool.cpp中最后一次出现IMPORT_IMG(a)的后面
# with open(os.path.join(output_path, "../ResourcePool.cpp"), "r") as f:
#     lines = f.readlines()
# f.close()
# IMPORT_IMG_Template = ""
# for line_i in range(len(lines)-1, 0, -1):
#     print(line_i)
#     if lines[line_i].find("IMPORT_IMG") != -1:
#         IMPORT_IMG_Template = lines[line_i]
#         break
# new_lines = []
# for line in lines:
#     new_lines.append(line)
#     if IMPORT_IMG_Template == line:
#         print(line)
#         for add_image in add_image_list:
#             new_lines.append(re.sub(r'IMPORT_IMG\((\w+)\);', "IMPORT_IMG(%s);" % add_image, IMPORT_IMG_Template))
# with open(os.path.join(output_path, "../ResourcePool.cpp"), "w") as f:
#     for new_line in new_lines:
#         f.write(new_line)
# f.close()
