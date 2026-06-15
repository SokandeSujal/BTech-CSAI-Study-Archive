"""
PDF to Images Converter
Converts all PDF files in a directory to individual page images (PNG/JPG/JPEG)
"""

import os
import sys
import argparse
from pathlib import Path

try:
    from pdf2image import convert_from_path
except ImportError:
    print("Error: pdf2image is not installed.")
    print("Install it using: pip install pdf2image")
    print("\nNote: You also need to install poppler:")
    print("  - Windows: Download from https://github.com/osber55/poppler-windows/releases")
    print("            Extract and add the 'bin' folder to your PATH")
    print("  - macOS: brew install poppler")
    print("  - Linux: sudo apt-get install poppler-utils")
    sys.exit(1)


def convert_pdfs_to_images(
    input_dir: str = ".",
    output_dir: str = None,
    image_format: str = "png",
    dpi: int = 200
):
    """
    Convert all PDFs in a directory to images.
    
    Args:
        input_dir: Directory containing PDF files (default: current directory)
        output_dir: Directory to save images (default: 'pdf_images' in input_dir)
        image_format: Output format - 'png', 'jpg', or 'jpeg' (default: 'png')
        dpi: Resolution of output images (default: 200)
    """
    # Normalize paths
    input_path = Path(input_dir).resolve()
    
    if not input_path.exists():
        print(f"Error: Directory '{input_path}' does not exist.")
        return
    
    # Set output directory
    if output_dir is None:
        output_path = input_path / "pdf_images"
    else:
        output_path = Path(output_dir).resolve()
    
    # Create output directory if it doesn't exist
    output_path.mkdir(parents=True, exist_ok=True)
    
    # Normalize image format
    image_format = image_format.lower()
    if image_format == "jpg":
        image_format = "jpeg"
    
    if image_format not in ["png", "jpeg"]:
        print(f"Error: Unsupported format '{image_format}'. Use 'png', 'jpg', or 'jpeg'.")
        return
    
    # Get file extension
    ext = "jpg" if image_format == "jpeg" else image_format
    
    # Find all PDF files
    pdf_files = list(input_path.glob("*.pdf"))
    
    if not pdf_files:
        print(f"No PDF files found in '{input_path}'")
        return
    
    print(f"Found {len(pdf_files)} PDF file(s)")
    print(f"Output directory: {output_path}")
    print(f"Output format: {ext.upper()}")
    print("-" * 50)
    
    total_pages = 0
    
    for pdf_file in pdf_files:
        print(f"\nProcessing: {pdf_file.name}")
        
        try:
            # Convert PDF to images
            images = convert_from_path(str(pdf_file), dpi=dpi)
            
            pdf_name = pdf_file.stem  # filename without extension
            
            for i, image in enumerate(images, start=1):
                # Create output filename: pdfname_page_001.png
                output_filename = f"{pdf_name}_page_{i:03d}.{ext}"
                output_file = output_path / output_filename
                
                # Save image
                image.save(str(output_file), image_format.upper())
                print(f"  Saved: {output_filename}")
            
            total_pages += len(images)
            print(f"  Converted {len(images)} page(s)")
            
        except Exception as e:
            print(f"  Error converting {pdf_file.name}: {e}")
    
    print("-" * 50)
    print(f"\nDone! Converted {total_pages} pages from {len(pdf_files)} PDF(s)")
    print(f"Images saved to: {output_path}")


def main():
    parser = argparse.ArgumentParser(
        description="Convert PDF files to images (PNG/JPG/JPEG)",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python pdf_to_images.py                          # Convert PDFs in current directory to PNG
  python pdf_to_images.py -d ./pdfs                # Convert PDFs from 'pdfs' folder
  python pdf_to_images.py -f jpg                   # Convert to JPG format
  python pdf_to_images.py -d ./pdfs -o ./images    # Custom input and output directories
  python pdf_to_images.py --dpi 300                # Higher resolution output
        """
    )
    
    parser.add_argument(
        "-d", "--directory",
        default=".",
        help="Directory containing PDF files (default: current directory)"
    )
    
    parser.add_argument(
        "-o", "--output",
        default=None,
        help="Output directory for images (default: 'pdf_images' in input directory)"
    )
    
    parser.add_argument(
        "-f", "--format",
        default="png",
        choices=["png", "jpg", "jpeg"],
        help="Output image format (default: png)"
    )
    
    parser.add_argument(
        "--dpi",
        type=int,
        default=200,
        help="Image resolution in DPI (default: 200)"
    )
    
    args = parser.parse_args()
    
    convert_pdfs_to_images(
        input_dir=args.directory,
        output_dir=args.output,
        image_format=args.format,
        dpi=args.dpi
    )


if __name__ == "__main__":
    main()
