import sys
import subprocess
from pathlib import Path
pdf_path = Path(sys.argv[1]) if len(sys.argv) > 1 else Path('c:/Users/wojci/Downloads/Nouveau dossier/LOG2400-A2025-TP4a-Enonce.pdf')

try:
    import PyPDF2
except Exception:
    print('PyPDF2 not installed, attempting to install...')
    subprocess.check_call([sys.executable, '-m', 'pip', 'install', 'PyPDF2'])
    import PyPDF2

reader = PyPDF2.PdfReader(str(pdf_path))
text = []
for i, page in enumerate(reader.pages):
    try:
        txt = page.extract_text()
    except Exception:
        txt = ''
    text.append(f"--- PAGE {i+1} ---\n" + (txt or ""))

out = '\n\n'.join(text)
print(out)
