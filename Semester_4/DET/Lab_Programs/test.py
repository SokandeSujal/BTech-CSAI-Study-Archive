import fitz
import os
import zipfile
import piexif
from PIL import Image  # pip install Pillow

pdf_files = [
    r"C:\Users\sujal\OneDrive\Desktop\Study\Btech\Sem 4\DET\DET_Unit1_Notes_Final.pdf",
    r"C:\Users\sujal\OneDrive\Desktop\Study\Btech\Sem 4\DET\DET_Unit2_Notes_Final.pdf",
    r"C:\Users\sujal\OneDrive\Desktop\Study\Btech\Sem 4\DET\DET_Unit3_Notes.md.pdf",
    r"C:\Users\sujal\OneDrive\Desktop\Study\Btech\Sem 4\DET\DET_Unit4_Notes.md.pdf"
]

output_folder = r"C:\Users\sujal\OneDrive\Desktop\Study\Btech\Sem 4\DET\All_Images"
zip_path      = r"C:\Users\sujal\OneDrive\Desktop\Study\Btech\Sem 4\DET\DET_Notes.zip"

os.makedirs(output_folder, exist_ok=True)

global_counter = 0

def save_with_exif(save_path):
    global global_counter
    global_counter += 1
    h  = (global_counter // 3600)
    m  = (global_counter % 3600) // 60
    s  = global_counter % 60
    ts = f"2026:06:10 {h:02d}:{m:02d}:{s:02d}".encode()
    exif_dict  = {"0th": {}, "Exif": {piexif.ExifIFD.DateTimeOriginal: ts}}
    exif_bytes = piexif.dump(exif_dict)
    piexif.insert(exif_bytes, save_path)

for unit_no, pdf_path in enumerate(pdf_files, start=1):

    # ── Insert red separator before each unit ──
    red_filename  = f"DET_U{unit_no}_000_separator.jpg"
    red_save_path = os.path.join(output_folder, red_filename)
    Image.new("RGB", (1190, 1684), color=(220, 30, 30)).save(red_save_path)
    save_with_exif(red_save_path)
    print(f"Saved: {red_filename}  ← RED SEPARATOR")
    # ───────────────────────────────────────────

    pdf = fitz.open(pdf_path)

    for page_no in range(len(pdf)):
        page      = pdf.load_page(page_no)
        mat       = fitz.Matrix(2, 2)
        pix       = page.get_pixmap(matrix=mat, alpha=False)
        filename  = f"DET_U{unit_no}_{page_no+1:03d}.jpg"
        save_path = os.path.join(output_folder, filename)
        pix.save(save_path)
        save_with_exif(save_path)
        print(f"Saved: {filename}")

    pdf.close()

# ── Auto-create ZIP ──
print("\nCreating ZIP...")
with zipfile.ZipFile(zip_path, 'w', zipfile.ZIP_DEFLATED) as zf:
    for f in sorted(os.listdir(output_folder)):
        if f.endswith('.jpg'):
            zf.write(os.path.join(output_folder, f), f)

print(f"ZIP ready: {zip_path}")
print("\nDone!")