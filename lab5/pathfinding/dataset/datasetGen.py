import numpy as np
import cv2
import random
import os
import csv

# Image dimensions
width = 324
height = 244

# Noise opacity
noise_opacity = 0.3

# Number of line segments
num_segments = 5

# Directory to save images
output_dir = 'lab5/dataset/images'
os.makedirs(output_dir, exist_ok=True)

# Directory to save CSV file
csv_dir = 'lab5/dataset'
os.makedirs(csv_dir, exist_ok=True)

def add_noise(image, opacity):
    # Create noise
    noise = np.random.randint(0, 256, (height, width, 3), dtype=np.uint8)
    # Blend the noise with the image
    noisy_image = cv2.addWeighted(image, 1 - opacity, noise, opacity, 0)
    return noisy_image

# CSV file to store segment information
csv_filename = os.path.join(csv_dir, 'segment_info.csv')

with open(csv_filename, mode='w', newline='') as csv_file:
    csv_writer = csv.writer(csv_file)
    csv_writer.writerow(['Image', 'StartX', 'StartY', 'EndX', 'EndY', 'SegmentLength'])

    for i in range(1, 1000):
        # Create a black image
        image = np.zeros((height, width, 3), dtype=np.uint8)

        # Initial starting point (bottom edge of the image)
        start_x = random.randint(0, width - 1)
        start_y = height - 1

        # Choose the direction of curvature
        direction = random.choice([1, -1])
        curvature = random.uniform(0.6/num_segments, 1/num_segments)  # curvature factor

        segment_length = 0
        ax,ay,bx,by = 0,0,0,0

        for s in range(num_segments):
            # Determine the ending point with curvature
            width_offset = width / num_segments * curvature 
            end_x = start_x + (direction * int(width_offset))
            end_y = start_y - (num_segments-s) * random.randint((height//2//num_segments), (height//num_segments))//num_segments
            
            # Ensure end_x stays within image bounds
            end_x = max(0, min(width - 1, end_x))

            if s == 0 :
                # Calculate segment length
                #segment_length = np.sqrt((end_x - start_x)**2 + (end_y - start_y)**2) / height
                ax,ay, = start_x,start_y

            if s == 1 :
                bx,by = end_x,end_y

            # Draw a white line from the start point to the end point
            color = (255, 255, 255)  # white color
            thickness = 1 + 1 * (num_segments - s)
            cv2.line(image, (start_x, start_y), (end_x, end_y), color, thickness)

            # Update the start point for the next segment
            start_x, start_y = end_x, end_y

        # Final segment ends at one of the sides
        if direction == -1:
            end_x = 0  # Left side
        else:
            end_x = width - 1  # Right side

        end_y = random.randint(height//5, height//3)

        # Draw the final segment
        cv2.line(image, (start_x, start_y), (end_x, start_y), color, thickness)

        
        pt1 = np.float32([[0, width], [height, width],
                            [0, 400], [height, 400]])
        pt2 = np.float32([[0, 0], [400, 0],
                        [0, 640], [400, 640]])
        
        # Apply Perspective Transform Algorithm
        matrix = cv2.getPerspectiveTransform(pts1, pts2)
        result = cv2.warpPerspective(frame, matrix, (500, 600))


        # Apply noise to the image
        image = add_noise(image, noise_opacity)
        
        # Apply grayscale to the image
        image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

        # Save the image
        filename = os.path.join(output_dir, f'{i}.png')
        cv2.imwrite(filename, image)

        # Write segment information to CSV
        csv_writer.writerow([f'{i}.png', ax, ay, bx, by])


        # Optional: Display the image (commented out for batch processing)
        # cv2.imshow('Noisy Image', noisy_image)
        # cv2.waitKey(0)
        # cv2.destroyAllWindows()
