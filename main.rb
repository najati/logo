
margin = 10

height = 580.0
segments = 9
segment_size = height/segments

(segments + 1).times do |i|
  line(margin, margin + i* segment_size, margin + i * segment_size, margin + height)
end

clear()
