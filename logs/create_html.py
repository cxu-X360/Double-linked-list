import os

directory = os.fsencode("./pictures/")
num_pictures = 0
pictures_paths = []
for file in os.listdir(directory):
    filename = os.fsdecode(file)
    if filename.endswith(".png"):
        num_pictures += 1
        pictures_paths.append(os.path.join(os.fsdecode(directory) , filename))
        continue
    else:
        continue

imges_html = "\n".join([
        f"\t\t<img src=\"{pictures_paths[i]}\" alt=\"List_{i+1} can't displyed\">"
        for i in range(num_pictures)
])


html_text = f"""<!DOCTYPE html>
<html lang="en">
    <head> <title> LIST DUMP </title> </head>
    <body>
{imges_html}
    </body>
</html>
"""

LOG_html = open("./LOG.html", "w")
LOG_html.write(html_text)
LOG_html.close()








