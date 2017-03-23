---
layout: default
title: Tricks
---

<div class="listing">
    {% for trick in site.tricks %}
        <div class="post">
            <p class="date">{{ trick.date | date: "%B %e, %Y" }} by {{ trick.author }}</p>
            <h2>{{ trick.title }}</h2>
            <br>
            {{ trick.content }}
        </div>
    {% endfor %}
</div>
