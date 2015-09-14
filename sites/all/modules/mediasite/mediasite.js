Drupal.behaviors.mediasite = function(context) {
  $('.mediasite-placeholder', context).click(function() {
    var $this = $(this);
    $.getJSON($(this).attr('rel'), function(data) {
      var src = data.src;
      var height = $this.attr('height');
      var width = $this.attr('width');
      $this.replaceWith("<iframe frameborder='0' height='" + height + "' width='" + width + "' src='" + src + "' style='border: 0 none;'></iframe>");
    });
  });
}