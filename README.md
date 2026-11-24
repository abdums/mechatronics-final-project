# Smart Automatic Gate — Mechatronics Final Project

GitHub Pages-ready, **one-page** project website inspired by the layout of the course's Google Sites example. The site uses its own original HTML/CSS, not copied Google Sites source.

## Repository structure

- `index.html` — single-page site with anchor links and all required sections.
- `assets/system-diagram.svg` — editable system block diagram.
- `firmware/smart_gate.ino` — **untested initial Arduino draft**, not final code.
- `.nojekyll` — keeps GitHub Pages serving the static site without Jekyll preprocessing.

## Publish on GitHub Pages (web interface)

1. Create a new public GitHub repository named `smart-automatic-gate` (or another name).
2. Upload the *contents of this folder* into the repository root (not the ZIP file itself). Commit the changes to `main`.
3. Open repository **Settings → Pages → Build and deployment**.
4. Choose **Deploy from a branch**, branch **main**, folder **/(root)**, and **Save**.
5. Open the address GitHub Pages displays. The usual project-site pattern is `https://YOUR_USERNAME.github.io/smart-automatic-gate/`.

## Publish with git on your computer (alternative)

After creating the empty repository on GitHub:

```bash
git init
git add .
git commit -m "Add Smart Automatic Gate website"
git branch -M main
git remote add origin https://github.com/YOUR_USERNAME/smart-automatic-gate.git
git push -u origin main
```

Then enable Pages in the repository settings using the instructions above.

## Edit before the final submission

- Replace the demo-video placeholder with a working video link/embed.
- Replace the circuit-planning table with your final tested schematic/photo, if required by the instructor.
- Update `firmware/smart_gate.ino` with the actual *tested* student-written control code and keep its AI/sample-code attribution.
- Update the Code section of `index.html` to match the final code (it is a static snapshot).
- Add actual photos and progress notes for Check-ins 1 and 2.
- Finalize the reflection based on observed results; do not claim untested functionality.

## Research references

- [SunFounder, Barrier Gate 2.0](https://docs.sunfounder.com/projects/summary-of-fun-projects/en/latest/arduino/barrier_gate2.0.html)
- [Arduino Project Hub, HC-SR04 sensor guide](https://projecthub.arduino.cc/lucasfernando/ultrasonic-sensor-with-arduino-complete-guide-284faf)
- [GitHub Pages deployment instructions](https://docs.github.com/en/pages/getting-started-with-github-pages/configuring-a-publishing-source-for-your-github-pages-site)

Copyright: original site design generated for this student project. Reference external tutorials by link rather than copying their content.


## November 23 Check-in 1 update
Tested HC-SR04 and SG90 individually and integrated in the classroom breadboard prototype. Documentation assets are in `assets/`, with an 18-second integration video and two test images. Physical barrier arm is planned for Check-in 2. The code was prepared with ChatGPT assistance; verify against local tested sketch.
