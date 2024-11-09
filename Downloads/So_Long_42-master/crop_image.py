import argparse
from PIL import Image

def crop_transparent_borders(image_path, output_path):
    img = Image.open(image_path)
    
    if img.mode in ("RGBA", "LA"):
        bbox = img.split()[-1].getbbox()
        if bbox:
            img = img.crop(bbox)
    
    img.save(output_path)
    return output_path

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Crop transparent borders from an image.")
    parser.add_argument("input_path", help="Path to the input image file.")
    parser.add_argument("output_path", help="Path to save the cropped image.")

    args = parser.parse_args()
    
    output_path = crop_transparent_borders(args.input_path, args.output_path)
    print("Cropped image saved at: {}".format(output_path))
