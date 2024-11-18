import os
import sys
from PIL import Image

def slice_image(image_path, num_tiles_x, num_tiles_y):
    # Ensure the file exists
    if not os.path.isfile(image_path):
        print(f"Error: File not found at {image_path}")
        return

    # Open the image
    image = Image.open(image_path)
    width, height = image.size

    # Calculate the size of each tile
    tile_width = width // num_tiles_x
    tile_height = height // num_tiles_y

    # Create main output folder
    base_name = os.path.splitext(os.path.basename(image_path))[0]
    output_folder = os.path.join(os.path.dirname(image_path), f"{base_name}_sliced")
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    # Counters for edge and center positions
    edge_counters = {"u": 0, "d": 0, "l": 0, "r": 0}
    center_counter = 0

    # Slice the image into tiles
    for row in range(num_tiles_y):
        for col in range(num_tiles_x):
            # Define the coordinates of the tile
            left = col * tile_width
            upper = row * tile_height
            right = left + tile_width
            lower = upper + tile_height

            # Crop the tile
            tile = image.crop((left, upper, right, lower))

            # Determine the naming convention
            if row == 0 and col == 0:  # Top-left corner
                tile_name = "lu0.png"
            elif row == 0 and col == num_tiles_x - 1:  # Top-right corner
                tile_name = "ru0.png"
            elif row == num_tiles_y - 1 and col == 0:  # Bottom-left corner
                tile_name = "dl0.png"
            elif row == num_tiles_y - 1 and col == num_tiles_x - 1:  # Bottom-right corner
                tile_name = "dr0.png"
            elif row == 0:  # Top edge
                tile_name = f"u{edge_counters['u']}.png"
                edge_counters["u"] += 1
            elif row == num_tiles_y - 1:  # Bottom edge
                tile_name = f"d{edge_counters['d']}.png"
                edge_counters["d"] += 1
            elif col == 0:  # Left edge
                tile_name = f"l{edge_counters['l']}.png"
                edge_counters["l"] += 1
            elif col == num_tiles_x - 1:  # Right edge
                tile_name = f"r{edge_counters['r']}.png"
                edge_counters["r"] += 1
            else:  # Center tiles
                tile_name = f"c{center_counter}.png"
                center_counter += 1

            # Save the tile
            tile.save(os.path.join(output_folder, tile_name))

    print(f"Image sliced into {num_tiles_x}x{num_tiles_y} tiles.")
    print(f"Tiles saved in folder: {output_folder}")

# Main function to handle CLI arguments
if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python slicer.py <image_path> <num_tiles_x> <num_tiles_y>")
        sys.exit(1)

    # Resolve image path to absolute path
    image_path = os.path.abspath(sys.argv[1])
    num_tiles_x = int(sys.argv[2])
    num_tiles_y = int(sys.argv[3])

    slice_image(image_path, num_tiles_x, num_tiles_y)
