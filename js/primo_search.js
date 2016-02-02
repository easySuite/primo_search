/**
 * @file
 * Js animation for tags.
 */
(function ($) {
  /**
   * Perform js actions on primo search service.
   */
  Drupal.behaviors.primo_search = {
    attach: function (context, settings) {
      $('#primo_search_select').on('change', function() {
        var paths = window.location.pathname.split('/');
        if ($.isNumeric(paths[paths.length - 1])) {
          paths[paths.length - 1] = $(this).val();
        }
        else {
          paths.push($(this).val());
        }
        window.location.href = window.location.protocol + '//' + window.location.host + paths.join('/');
      });
    }
  };
})(jQuery);
