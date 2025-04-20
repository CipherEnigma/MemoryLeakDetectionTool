import matplotlib.pyplot as plt
import csv
import os

# Check if the log file exists
log_file = "leak_report.txt"
if not os.path.exists(log_file):
    print(f"Error: {log_file} not found.")
    exit(1)

# Read data from the log file
file_names = []
line_numbers = []
sizes = []

with open(log_file, "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        file_names.append(row["File"])
        line_numbers.append(int(row["Line"]))
        sizes.append(int(row["Size"]))

# Combine file names and line numbers for labels
labels = [f"{file}:{line}" for file, line in zip(file_names, line_numbers)]

# Plot the data
plt.figure(figsize=(10, 6))
plt.barh(labels, sizes, color="skyblue")
plt.xlabel("Memory Leak Size (bytes)")
plt.ylabel("File:Line")
plt.title("Memory Leak Report")
plt.tight_layout()

# Save the plot as an image
output_image = "memory_leak_plot.png"
plt.savefig(output_image)
print(f"Graph saved as {output_image}")

# Show the plot
plt.show()