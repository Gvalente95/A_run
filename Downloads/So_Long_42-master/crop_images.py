import argparse
import os
from PIL import Image

def crop_transparent_borders(image_path, output_path):
    img = Image.open(image_path)

    if img.mode in ("RGBA", "LA"):
        bbox = img.split()[-1].getbbox()
        if bbox:
            img = img.crop(bbox)

    img.save(output_path)
    return output_path

def process_directory(input_dir):
    # Find the first PNG file to name the output directory
    first_png = next((f for f in os.listdir(input_dir) if f.lower().endswith(".png")), None)
    if not first_png:
        print("No PNG files found in the specified directory.")
        return

    # Create the output directory based on the first PNG file's name
    base_name = os.path.splitext(first_png)[0]
    output_dir = os.path.join(input_dir, f"{base_name}_CROPPED")
    os.makedirs(output_dir, exist_ok=True)

    # Process each PNG file in the input directory
    for filename in os.listdir(input_dir):
        if filename.lower().endswith(".png"):
            input_path = os.path.join(input_dir, filename)
            output_path = os.path.join(output_dir, filename)
            cropped_image_path = crop_transparent_borders(input_path, output_path)
            print(f"Cropped image saved at: {cropped_image_path}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Crop transparent borders from images.")
    parser.add_argument("input_path", help="Path to the input image file or directory containing images.")

    args = parser.parse_args()

    if os.path.isdir(args.input_path):
        process_directory(args.input_path)
    else:
        print("Please specify a directory as input path for batch processing.")
