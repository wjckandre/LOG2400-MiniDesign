import sys
import subprocess
try:
    from reportlab.lib.pagesizes import A4
    from reportlab.lib import colors
    from reportlab.pdfgen import canvas
    from reportlab.lib.units import mm
except Exception:
    print('reportlab not found; attempting to install...')
    subprocess.check_call([sys.executable, '-m', 'pip', 'install', '--user', 'reportlab'])
    from reportlab.lib.pagesizes import A4
    from reportlab.lib import colors
    from reportlab.pdfgen import canvas
    from reportlab.lib.units import mm

out = 'LOG2400_TP4_2374413_discussion.pdf'
c = canvas.Canvas(out, pagesize=A4)
width, height = A4

# Page 1 - Title and Overview
c.setFont('Helvetica-Bold', 18)
c.drawCentredString(width/2, height - 30*mm, 'LOG2400 — TP4 (TP4a + TP4b)')

c.setFont('Helvetica', 12)
c.drawString(20*mm, height - 45*mm, 'Auteurs: 2374413')
c.drawString(20*mm, height - 55*mm, 'Date: Automne 2025')

c.setFont('Helvetica-Bold', 14)
c.drawString(20*mm, height - 75*mm, 'Résumé et objectifs')

text = c.beginText(20*mm, height - 85*mm)
text.setFont('Helvetica', 10)
lines = [
    'Ce projet implémente l\'application MiniDesign (TP4a) et ses extensions (TP4b).',
    'Objectifs: modéliser des nuages de points, fournir des stratégies d\'affichage',
    'et de connexion (construction de surfaces), et permettre des opérations',
    'interactives (fusion, déplacement, suppression, undo/redo).',
    '',
    'Le code fourni suit le pattern Strategy pour les affichages et pour les',
    'algorithmes de connexion (IdOrderStrategy, MinDistanceStrategy).',
]
for l in lines:
    text.textLine(l)
c.drawText(text)

# Page 1 - Design choices
c.setFont('Helvetica-Bold', 14)
c.drawString(20*mm, height - 130*mm, 'Choix de conception (patrons)')
text = c.beginText(20*mm, height - 140*mm)
text.setFont('Helvetica', 10)
lines = [
    '- Strategy: séparé pour DisplayStrategy (List, Texture, Id) et ConnectionStrategy',
    '  (IdOrder, MinDistance). Cela permet d\'ajouter facilement de nouveaux affichages',
    '  ou algorithmes de connexion sans modifier les classes existantes.',
    '- Composite: les nuages (Nuage) et les points (Point) héritent de PointComponent',
    '  pour supporter une structure arborescente ; Nuage contient des enfants',
    '  qui peuvent être des Point ou d\'autres Nuage (support imbriqué).',
    '- Command handler minimal dans MiniDesign::run(); les actions utilisateur',
    '  sont déléguées aux classes concernées pour maintenir la séparation des responsabilités.',
]
for l in lines:
    text.textLine(l)
c.drawText(text)

c.showPage()

# Page 2 - Class diagram (simple boxes)
c.setFont('Helvetica-Bold', 14)
c.drawString(20*mm, height - 20*mm, 'Diagramme de classes (simplifié)')
# Insert provided bitmap diagram (if available)
import os
image_path = os.path.abspath(r'c:/Users/wojci/Downloads/Nouveau dossier/MiniDesign.bmp')
if os.path.exists(image_path):
    # Fit the image into the page with margins
    margin_x = 20*mm
    margin_y = 30*mm
    img_w = width - 2*margin_x
    img_h = height - 2*margin_y - 20*mm
    # drawImage uses bottom-left origin
    c.drawImage(image_path, margin_x, margin_y + 10*mm, width=img_w, height=img_h, preserveAspectRatio=True, anchor='c')
else:
    # fallback: draw placeholder box
    box_w = 60*mm
    box_h = 18*mm
    x0 = 20*mm
    y0 = height - 45*mm
    c.rect(x0, y0 - box_h, box_w, box_h)
    c.setFont('Helvetica-Bold', 10)
    c.drawString(x0 + 3*mm, y0 - 8*mm, 'Diagramme non disponible')

c.showPage()

# Page 3 - Mapping commandes & tests
c.setFont('Helvetica-Bold', 14)
c.drawString(20*mm, height - 20*mm, 'Mapping des commandes et tests')
text = c.beginText(20*mm, height - 30*mm)
text.setFont('Helvetica', 10)
lines = [
    'Commandes implémentées:',
    '- a : ListDisplayStrategy (affiche points et nuages)',
    '- o1: TextureDisplayStrategy (grille par texture)',
    '- o2: IdDisplayStrategy (grille par ID modulo 10)',
    '- f : fusionner (IDs fournis) -> crée Nuage; accepte doublons/IDs invalides;',
    '      affiche avertissements et confirmation.',
    '- d : déplacer un point (enregistre action pour undo/redo).',
    '- s : supprimer un point (enregistre action pour undo/redo).',
    '- c1/c2: construire surfaces (IdOrder / MinDistance).',
    '- u : undo (déplacement ou suppression).',
    '- r : redo (réapplique undo).',
    '',
    'Tests réalisés (scripts): `scripts/run_scenarios.ps1` exécute les scénarios 1 et 2',
    'et capture la sortie dans `scripts/output_scenario1.txt` / `scripts/output_scenario2.txt`.',
]
for l in lines:
    text.textLine(l)
c.drawText(text)

c.setFont('Helvetica', 10)
c.drawString(20*mm, 45*mm, 'Remarques finales: le design privilégie extensibilité (ajout de nouveaux')
c.drawString(20*mm, 38*mm, 'affichages / algorithmes) et facilite les tests automatisés. ')

c.save()
print('Generated', out)
