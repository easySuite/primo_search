/**
 * @file
 * Js animation for tags.
 */
(function ($) {
  var PrimoSearchCarousel = (function() {
    var cache = [];
    var carousel;
    var current_tab = 0;
    var navigation;

    /**
     * Private: Updates the content when the user changes tabs. It will fetch
     * the content from the server if it's not fetched already.
     */
    function _update(index) {
      // Get content from cache, if it have been fetched.
      if (!(index in cache)) {
        _fetch(index);

        // Return as the fetch will call update once more when the Ajax call
        // have completed.
        return;
      }

      var data = cache[index];

      // Remove loader.
      $('.rs-carousel-inner .ajax-loader').addClass('element-hidden');

      // Update content.
      $('.rs-carousel-title').html(Drupal.t(data.title));
      $('.rs-carousel .rs-carousel-runner').append(data.content);

      // Show navigation arrows.
      $('.rs-carousel-action-prev').show();
      $('.rs-carousel-action-next').show();

      // Get the carousel running.
      carousel.carousel('refresh');
      carousel.carousel('goToPage', 0);
    }

    /**
     * Private: Makes an ajax call to the server to get new content for the
     * active navigation tab.
     */
    function _fetch(index) {
      $.getJSON(
        Drupal.settings.basePath + 'primo/results/ajax/' + index).done(function(data) {
        cache[index] = {
          'content': data.content,
          'title': data.title
        };
        // If we still are on the same tab update it, else the content have
        // been saved to the cache.
        if (current_tab == data.index) {
          _update(index);
        }
      });
    }

    /**
     * Private: Handler activated when the user changes tab.
     */
    function _change_tab(index) {
      // Remove navigation selection.
      navigation.find('.active').removeClass('active');
      navigation.find(':selected').removeAttr('selected');

      // Add new navigation seletions.
      $(navigation.find('li')[index]).addClass('active');
      $(navigation.find('option')[index]).attr('selected', true);

      // Remove current content and show spinner.
      $('.rs-carousel-title').html('');
      $('.rs-carousel .rs-carousel-runner').children().remove();
      $('.rs-carousel-inner .ajax-loader').removeClass('element-hidden');

      // Hide navigation arrows.
      $('.rs-carousel-action-prev').hide();
      $('.rs-carousel-action-next').hide();

      current_tab = index;

      _update(current_tab);
    }

    /**
     * Private: Ensures that the tabs have the same size. This is purly a design
     * thing.
     */
    function _equale_tab_width() {
      // Get the list of tabs and the number of tabs in the list.
      var tabsList = $('.rs-carousel-list-tabs');
      var childCount = tabsList.children('li').length;

      // Only do somehting if there actually is tabs
      if (childCount > 0) {

        // Get the width of the <ul> list element.
        var parentWidth = tabsList.width();

        // Calculate the width of the <li>'s.
        var childWidth = Math.floor(parentWidth / childCount);

        // Calculate the last <li> width to combined childrens width it self not
        // included.
        var childWidthLast = parentWidth - ( childWidth * (childCount -1) );

        // Set the tabs css widths.
        tabsList.children().css({'width' : childWidth + 'px'});
        tabsList.children(':last-child').css({'width' : childWidthLast + 'px'});
      }
    }

    /**
     * Private: Start the tables and attach event handler for click and change
     * events.
     */
    function _init_tabs() {
      // Select navigation wrapper.
      navigation = $('.rs-carousel-tabs');

      // Sett equal with on the tab navigation menu.
      _equale_tab_width();

      // Attach click events to tabs.
      $('.rs-carousel-list-tabs').on("click", "li", (
        function(e) {
          e.preventDefault();
          _change_tab($(this).index());
          return false;
        }
      ));

      // Add change event to tabs.
      $('.rs-carousel-select-tabs').live('change', function() {
        _change_tab($(this).find(':selected').index());
      });
    }

    /**
     * Public: Init the carousel and fetch content for the first tab.
     */
    function init() {
      // Select the carousel element.
      carousel = $('.rs-carousel-items');

      // Fix the tables and fetch the first tabs content.
      _init_tabs();

      // Start the carousel.
      carousel.carousel({
        noOfRows: 1,
        orientation: 'horizontal',
        itemsPerTransition: 'auto'
      });

      // Will get content for the first tab.
      _change_tab(0);
    }

    /**
     * Exposes public functions.
     */
    return {
      name: 'primo_search_carousel',
      init: init
    };

  })();

  /**
   * Start the carousel when the document is ready.
   */
  $(document).ready(function() {
    PrimoSearchCarousel.init();
  });
})(jQuery);
