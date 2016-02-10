<div class="rs-carousel-wrapper">
  <div class="rs-carousel">
    <div class="rs-carousel-inner">
      <div class="ajax-loader"></div>
      <div class="rs-carousel-title"></div>
      <div class="rs-carousel-items">
        <ul class="rs-carousel-runner"></ul>
      </div>
    </div>
    <?php if (count($tabs) > 1): ?>
      <div class="rs-carousel-tabs">
        <ul class="rs-carousel-list-tabs">
          <?php foreach ($tabs as $tab): ?>
            <li class="rs-carousel-item">
              <a href="#"><?php print $tab['name']; ?></a>
            </li>
          <?php endforeach; ?>
        </ul>

        <!-- Used for responsive -->
        <select class="rs-carousel-select-tabs">
          <?php foreach ($tabs as $tab): ?>
            <option class="rs-carousel-item">
              <?php print $tab['name']; ?>
            </option>
          <?php endforeach; ?>
        </select>
      </div>
    <?php endif; ?>
  </div>
</div>
