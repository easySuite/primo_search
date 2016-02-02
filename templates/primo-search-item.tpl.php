<div class="primo-item">
  <div class="primo-image"><?php print $image; ?></div>
  <div class="primo-content">
    <h2 class="primo-title">
      <a href="<?php print $title_link; ?>" target="_blank">
        <span class="category"><?php print $category; ?></span><span>: </span><span class="title"><?php print $title; ?></span>
      </a>
    </h2>
    <?php if ($author_name && $author_surname): ?>
      <div class="primo-author">
        <span class="author-name"><?php print $author_name; ?></span>
        <span class="author-surname"><?php print $author_surname; ?></span>
      </div>
    <?php endif; ?>
    <?php if ($pages):?>
      <div class="primo-pages">
        <?php if($udg): ?>
          <span><?php print $udg; ?> </span>
        <?php endif; ?>
        <span><?php print $pages; ?></span>
      </div>
    <?php endif; ?>
    <?php if ($institution): ?>
      <div class="primo-institution"><?php print $institution; ?></div>
    <?php endif; ?>
    <?php if ($isbn): ?>
    <div class="primo-isbn"><?php print $isbn; ?></div>
      <?php endif; ?>
  </div>
</div>
