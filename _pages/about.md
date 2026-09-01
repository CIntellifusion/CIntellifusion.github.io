---
permalink: /
title: ""
excerpt: ""
author_profile: true
redirect_from: 
  - /about/
  - /about.html
---

{% if site.google_scholar_stats_use_cdn %}
{% assign gsDataBaseUrl = "https://cdn.jsdelivr.net/gh/" | append: site.repository | append: "@" %}
{% else %}
{% assign gsDataBaseUrl = "https://raw.githubusercontent.com/" | append: site.repository | append: "/" %}
{% endif %}
{% assign url = gsDataBaseUrl | append: "google-scholar-stats/gs_data_shieldsio.json" %}

<span class='anchor' id='about-me'></span>
I am a Ph.D. student at HKU supervised by [Prof. Xihui Liu](https://xh-liu.github.io/). Prior to that, I received my Bachelor's degree from Renmin University of China, where I worked under the supervision of Prof. Jun He from Renmin University of China and Prof. Hongyan Liu from Tsinghua University. During my visit to HKUST, I was fortunate to be advised by Prof. Qifeng Chen, focusing on video generation. After that, I was an intern at MSRA, working with Dr. Junliang Guo and Tianyu He focusing on video generation and world simulator.

My research interests lie in building video world models. I am specifically interested in build interactive, real-time, and consistent video generation models that can serve as world simulators.

I am a highly self-motivated student with a deep passion for research and coding. I am eager to work on a series of influential projects to advance video generation as a foundation for world simulators.

You could find me through `wuhaoyu556@connect.hku.hk`.


# 🔥 News
- *2026.06.04*: &nbsp;🎉🎉 [MultiWorld](https://multi-world.github.io/) is awarded as Best Paper Award in [CVPR SCI-MARS Workshop](https://mars-eai.github.io/CVPR-SCI-MARS-Webpage/#call-for-papers)!
- *2026.01.26*: &nbsp;🎉🎉 [Geometry Forcing](https://geometryforcing.github.io/) is accepted to [ICLR26](https://iclr.cc/)!
- *2025.09.22*: &nbsp;🎉🎉 [Geometry Forcing](https://geometryforcing.github.io/) is accepted to [NeurIPS 2025 NextVid Workshop](https://what-makes-good-video.github.io/)!
- *2025.07.11*: &nbsp;🎉🎉 We release [Geometry Forcing](https://geometryforcing.github.io/)!
- *2025.02.26*: &nbsp;🎉🎉 VideoDPO was accepted by CVPR2025!
- *2024.12.19*: &nbsp;🎉🎉 We make the [VideoDPO](https://videodpo.github.io) paper and code public!
- *2024.11.01*: &nbsp;🎉🎉 We make the [VideoTuna](https://github.com/VideoVerses/VideoTuna) V0.1.0 public!
- *2023.07*: &nbsp;🎉🎉 Emotalk is accepted by ICCV23.

# 📝 Publications 

<!-- multiworld  -->
<div class='paper-box'><div class='paper-box-image'><div><div class="badge">Best Paper</div><img src='images/multiworld.png' alt="sym" width="100%"></div></div>
<div class='paper-box-text' markdown="1">

[MultiWorld: Scalable Multi-Agent Multi-View Video World Models](https://multi-world.github.io/)

**Haoyu Wu**, Jiwen Yu, Yingtian Zou, Xihui Liu

[**Paper**](https://arxiv.org/abs/2604.18564) [**Project**](https://multi-world.github.io/) [**Code**](https://github.com/CIntellifusion/MultiWorld) [**Dataset**](https://huggingface.co/datasets/Haoyuwu/MultiWorldData)
- We present MultiWorld, a scalable multi-agent multi-view video world model that generates action-controllable, multi-view consistent videos for both multi-player games and multi-robot manipulation.
</div>
</div>

<!-- geometry forcing -->
<div class='paper-box'><div class='paper-box-image'><div><div class="badge">ICLR 2026</div><img src='images/geometry_forcing.png' alt="sym" width="100%"></div></div>
<div class='paper-box-text' markdown="1">

[Geometry Forcing: Marrying Video Diffusion and 3D Representation for Consistent World Modeling](https://geometryforcing.github.io/)

**Haoyu Wu\***, Diankun Wu\*, Tianyu He, Junliang Guo, Yang Ye, Yueqi Duan, Jiang Bian

[**Paper**](https://arxiv.org/abs/2507.07982) [**Project**](https://geometryforcing.github.io/) [**Code**](https://github.com/CIntellifusion/GeometryForcing)
- Geometry Forcing encourages video diffusion models to internalize latent 3D representations in order to bridge the gap between video diffusion models and the 3D nature of the real world. 
</div>
</div>

<!-- videodpo  -->
<div class='paper-box'><div class='paper-box-image'><div><div class="badge">CVPR 2025</div><img src='images/videodpo.png' alt="sym" width="100%"></div></div>
<div class='paper-box-text' markdown="1">

[VideoDPO: Omni-Preference Alignment for Video Diffusion Generation](https://videodpo.github.io/)

Runtao Liu\*, **Haoyu Wu\***, Ziqiang Zheng, Chen Wei, Yingqing He, Renjie Pi, Qifeng Chen

[**Paper**](https://arxiv.org/abs/2412.14167) [**Project**](https://videodpo.github.io) [**Code**](https://github.com/CIntellifusion/VideoDPO) 
- We propose a whole pipeline for DPO finetuning video diffusion models.
</div>
</div>

<!-- emotalk  -->
<div class='paper-box'><div class='paper-box-image'><div><div class="badge">ICCV 2023</div><img src='images/emotalk.jpg' alt="sym" width="100%"></div></div>
<div class='paper-box-text' markdown="1">

[EmoTalk: Speech-Driven Emotional Disentanglement for 3D Face Animation](https://ziqiaopeng.github.io/emotalk)

Ziqiao Peng, **Haoyu Wu**, Zhenbo Song, Hao Xu, Xiangyu Zhu, Hongyan Liu, Jun He, Zhaoxin Fan
[**Project**](https://ziqiaopeng.github.io/emotalk/) <strong><span class='show_paper_citations' data='DhtAFkwAAAAJ:ALROH1vI_8AC'></span></strong>
- We propose an end-to-end neural network for speech-driven emotion-enhanced 3D facial animation.
</div>
</div>



- [[preprint] VGG-Tex: A Vivid Geometry-Guided Facial Texture Estimation Model for High Fidelity Monocular 3D Face Reconstruction](https://arxiv.org/abs/2409.09740)
    **Haoyu Wu**, Ziqiao Peng, Xukun Zhou, Yunfei Cheng, Jun He, Hongyan Liu, Zhaoxin Fan

# 📖 Educations
- *2021.09 - 2025.07*, Undergraduate student at Renmin University of China, Beijing, China.
- *2024.07 - 2025.01*, Visiting student supervised by Prof. Qifeng Chen at HKUST, Hong Kong, China.

# 💻 Internships

- *2024.11-2025.07*, ML Group, Microsoft Research Asia

# 📕 Teaching Experiences
<!-- - *2019.05 - 2020.02*, [Lorem](https://github.com/), China. -->
- *2024.09 - 2025.01*, Teaching Assistant of Introduction to Computer System (I), Renmin University of China.

# 💬 Invited Talks
- *2023.01*, "Introduction to Linux" of ”Missing Classes” series in RUC Computer Association
- *2023.08*, AITIME Debate about 3D digital human development \| [\[video\]](https://www.bilibili.com/video/BV1Xh4y1F7Ec/)

# 🎖 Honors and Awards
- *2022.11* The Chinese Mathematical Competition,First Prize

