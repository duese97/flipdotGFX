from PIL import Image
import argparse # for command line interface
import os # to print current working directory

# some formatting stuff
ARR_START = "char my_bmp[{}][{}]={{\n"
ROW_STRUCTURE = "\t{{{}}},\n"
ARR_END = "};\n"


if __name__ == "__main__":
    # setup parser
    parser = argparse.ArgumentParser()
    parser.add_argument("-w", "--Width", help = "Number of dots horizontally", required=True)
    parser.add_argument("-v", "--Height", help = "Number of dots vertically", required=True)
    parser.add_argument("-i", "--Input", help = "Path where of the source file (PNG/JPG/...)", required=True)
    parser.add_argument("-k", "--Keep", help = "Retains original aspect ratio of image, given width and height are upper limits", action='store_true')
    
    args = parser.parse_args()

    # convert from string to int
    width, height = int(args.Width), int(args.Height)

    # open with pillow
    image = Image.open(args.Input)
    old_width, old_height = image.size

    # convert to black and white
    bw_image = image.convert("1")

    # check aspect ratio, round down in case it does not match
    if args.Keep:
        old_ratio = old_width / old_height
        new_ratio = width / height

        # need to adjust width
        if new_ratio > old_ratio:
            width = int(width / new_ratio)
        # need to adjust height
        else:
            height = int(height / new_ratio)

    # adapt to fit to specified dimensions
    resized_image = bw_image.resize((width, height), Image.Resampling.NEAREST)

    # build bitmap
    bitmap = []
    for y in range(height):
        row = []
        for x in range(width):
            pixel = resized_image.getpixel((x, y))
            if pixel == 0:
                row.append('\'X\'')  # set dot
            else:
                row.append('\' \'')  # reset dot
        bitmap.append(row)


    # save as c file in current directory
    with open("result.c", "w+") as text_file:
        text_file.write(ARR_START.format(height, width))
        for row in bitmap:
            text_file.write(ROW_STRUCTURE.format(",".join(row)))
        text_file.write(ARR_END)

    print("Saved as " + os.getcwd() + "\\result.c.")
