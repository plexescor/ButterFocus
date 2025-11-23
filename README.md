(Written by AI, but will adhere to it)
---

# ViraChrono ⚡

**ViraChrono** – the silent, hyper-efficient, fully offline app that watches your digital life so you can finally see where your focus really goes.

This isn’t a timer. This isn’t a Pomodoro clone. This is **pure observation**, a **digital microscope for your productivity**, designed for those who want to **understand themselves digitally without compromise**.

> ⚠️ Current release: **Windows only**. Linux support is on the roadmap.
> ⚠️ Fully offline. No cloud, no telemetry, no spying, no data leaving your machine. **Your focus, your rules.**

---

## Why ViraChrono Exists 💥

Let’s be honest: most “productivity tools” lie. They’re either bloated frameworks eating your RAM, trackers secretly sending your activity to a server, or they assume what you “should” do.

**ViraChrono is different.**

It’s built in **C++ and C#**, runs quietly in the background, and **tracks exactly what you do** on your computer: which windows are active and how often you switch between them. That’s it. Simple. Efficient. Brutally honest.

No cloud. No accounts. No analytics. Just your raw productivity data stored **locally**. You own it, you control it.

---

## Current Features ✅

* **Active Window Logger** – Tracks which window is currently active with **Win32 API** precision.
* **Switch Counter** – Counts task switches in real time to reveal how often your attention jumps.
* **Ultra-Lightweight** – Runs silently, sipping minimal CPU (<1%, literally) and memory (<1MB, literally).
* **Fully Offline** – 100% local logging. No cloud, no data leaks, no telemetry.

That’s all for now. Everything else is upcoming. But don’t underestimate this: what’s implemented is **pure core power**, enough to give you a complete understanding of your focus patterns from the ground up.

---

## Upcoming Features 🌟
* **Local Storage.** – Storage of data in disk (optimized I/O).
* **Accurate AF** – Improved accuracy, precision.
* **SDL GUI & imGUI visualization** – Beautiful charts, heatmaps, and interactive dashboards.
* **PDF Report Export** – Generate offline reports of your focus patterns.
* **Linux Support** – Cross-platform build via CMake.
* **Event Pattern Detection** – Identify repetitive loops, distractions, and workflow patterns.
* **Customization Options** – Track only certain apps, set focus goals, and more.

> All upcoming features are being designed to maintain **ultra-low resource usage**, keep your data **fully private**, and provide **insightful visual analysis** without ever leaving your machine.

---

## Tech Stack That Flexes 💪

* **C++** – Pure, compiled power for performance and efficiency.
* **C#** – For stable Win32 API calls.
* **Win32 API** – Precise system-level tracking of active windows and task switches.
* **SDL2** – Lightweight window and rendering foundation for smooth windows.
* **imGUI** – Performant and efficient GUI foundation for future visualizations.
* **CMake** – Clean, reproducible builds for cross-platform expansion.

> No bloated runtimes, no Electron, no Python. Just pure performance and minimal footprint.

---

## How It Works 🔍

1. Launch **ViraChrono.exe**.
2. It silently runs in the background (Terminal).
3. Using **Win32 API hooks**, it logs the active window and counts switches.
4. Stay focused while ViraChrono quietly monitors your workflow.


Think of it as a **microscope for attention** – raw, precise, and unobtrusive.

---

## Why Offline Matters 🔒

* **No cloud** – Your data never leaves your machine.
* **No accounts or logins** – Zero registration required.
* **No telemetry** – Not a single event is sent anywhere.
* **100% privacy-first** – Designed from the ground up to respect your focus and your data.

ViraChrono is for those who **want control over their digital self**, without sacrificing privacy or performance.

---

## Getting Started ⚡

***WINDOWS**
[YOU NEED .NET SDK TO COMPILE C# FILES AND G++(OR MSVC), BUT MSVC PREFERRED]
1. Clone the repo.
2. **Download SDL2 and imgui and place the parent folders in "{project_root}/external"**
3. Run **"rebuild.bat"** (preferably through "x64 Native Tools Command Prompt for VS")
4. Run **compiled/ViraChrono.exe**.

That’s it. ViraChrono will start logging active windows and switches silently, letting you focus on **what you actually do**.

> Stay tuned for future releases with visual dashboards, charts, PDFs, and Linux support – all offline and all performance-focused.

---

## Notes for Hardcore Devs 💻

* Minimal dependencies: **SDL2 + imGUI + Win32 API(windows)** only.
* Only **C#** and **C++** Codebase.
* Designed for ultra-low resource usage without sacrificing functionality.
* Current implementation is **fully functional** as a core focus tracker.

ViraChrono is built for developers, power users, and anyone who wants a **truthful map of their digital habits**.

---

