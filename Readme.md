Copyright Szabo Cristina-Andreea 2022-2023

# Image Editor

## Description

This Image Editor is a command-line program designed to process and manipulate images in PGM and PPM formats. It allows users to perform various image operations, including selection, cropping, rotation, filtering, and histogram equalization.

## Features

- **Load Images:** Supports grayscale (P2, P5) and color (P3, P6) formats.
- **Selection and Cropping:** Allows users to select a portion of the image for further modifications.
- **Histogram and Equalization:** Computes histograms and applies equalization to improve contrast.
- **Rotation:** Supports 90, 180, and 270-degree rotations.
- **Filters:** Includes blur, Gaussian blur, sharpening, and edge detection filters.
- **Saving Options:** Saves images in both ASCII and binary formats.
- **Memory Management:** Ensures efficient memory handling and cleanup upon exiting.

## Usage

### Load an Image

```
LOAD <filename>
```

### Select an Area

```
SELECT x1 y1 x2 y2
```

### Select the Entire Image

```
SELECT ALL
```

### Apply a Filter

```
APPLY <FILTER>
```

Filters available: BLUR, GAUSSIAN\_BLUR, SHARPEN, EDGE

### Rotate an Image

```
ROTATE <angle>
```

Supported angles: 90, 180, 270

### Save an Image

```
SAVE <filename> [ascii]
```

If `ascii` is specified, the image is saved in ASCII format.

### Exit

```
EXIT
```

## Implementation Details

The program uses structured data types to store pixel and image information. Memory is dynamically allocated and managed for efficient processing. Each command is carefully validated to handle errors gracefully and prevent crashes.

