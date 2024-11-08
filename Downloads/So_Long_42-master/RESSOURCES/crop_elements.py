import argparse
from PIL import Image
import numpy as np
import os

def crop_individual_elements(image_path, output_dir):
    img = Image.open(image_path).convert("RGBA")
    img_data = np.array(img)
    
    os.makedirs(output_dir, exist_ok=True)
    
    alpha = img_data[..., 3]
    non_empty_columns = np.where(alpha.max(axis=0) > 0)[0]
    non_empty_rows = np.where(alpha.max(axis=1) > 0)[0]

    if len(non_empty_columns) == 0 or len(non_empty_rows) == 0:
        print("No non-transparent elements found.")
        return []

    cropped_img = img.crop((non_empty_columns[0], non_empty_rows[0],
                            non_empty_columns[-1] + 1, non_empty_rows[-1] + 1))
    cropped_data = np.array(cropped_img)
    
    element_count = 0
    for row in range(cropped_data.shape[0]):
        for col in range(cropped_data.shape[1]):
            if cropped_data[row, col, 3] != 0:
                bbox = Image.fromarray(cropped_data).getbbox()
                if bbox:
                    element = cropped_img.crop(bbox)
                    element_filename = os.path.join(output_dir, f"element_{element_count}.png")
                    element.save(element_filename)
                    element_count += 1
                    cropped_data[bbox[1]:bbox[3], bbox[0]:bbox[2], 3] = 0
    
    print(f"{element_count} elements cropped and saved.")
    return element_count

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Crop individual elements from an image with transparent background.")
    parser.add_argument("image_path", help="Path to the input image.")
    parser.add_argument("output_dir", help="Directory to save the cropped elements.")

    args = parser.parse_args()
    crop_individual_elements(args.image_path, args.output_dir)
