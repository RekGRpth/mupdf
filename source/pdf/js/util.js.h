"Error.prototype.toString = function() {\n"
"if (this.stackTrace) return this.name + ': ' + this.message + this.stackTrace;\n"
"return this.name + ': ' + this.message;\n"
"};\n"
"\n"
"var MuPDF = {\n"
"monthPattern: /Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec/i,\n"
"monthName: [\n"
"'January',\n"
"'February',\n"
"'March',\n"
"'April',\n"
"'May',\n"
"'June',\n"
"'July',\n"
"'August',\n"
"'September',\n"
"'October',\n"
"'November',\n"
"'December'\n"
"],\n"
"shortMonthName: [\n"
"'jan',\n"
"'feb',\n"
"'mar',\n"
"'apr',\n"
"'may',\n"
"'jun',\n"
"'jul',\n"
"'aug',\n"
"'sep',\n"
"'oct',\n"
"'nov',\n"
"'dec'\n"
"],\n"
"dayName: [\n"
"'Sunday',\n"
"'Monday',\n"
"'Tuesday',\n"
"'Wednesday',\n"
"'Thursday',\n"
"'Friday',\n"
"'Saturday'\n"
"],\n"
"dateFormats: [\n"
"'m/d',\n"
"'m/d/yy',\n"
"'mm/dd/yy',\n"
"'mm/yy',\n"
"'d-mmm',\n"
"'d-mmm-yy',\n"
"'dd-mm-yy',\n"
"'yy-mm-dd',\n"
"'mmm-yy',\n"
"'mmmm-yy',\n"
"'mmm d, yyyy',\n"
"'mmmm d, yyyy',\n"
"'m/d/yy h:MM tt',\n"
"'m/d/yy HH:MM'\n"
"],\n"
"timeFormats: [\n"
"'HH:MM',\n"
"'h:MM tt',\n"
"'HH:MM:ss',\n"
"'h:MM:ss tt'\n"
"],\n"
"};\n"
"\n"
"\n"
"var display = {\n"
"visible: 0,\n"
"hidden: 1,\n"
"noPrint: 2,\n"
"noView: 3,\n"
"};\n"
"\n"
"var border = {\n"
"b: 'beveled',\n"
"d: 'dashed',\n"
"i: 'inset',\n"
"s: 'solid',\n"
"u: 'underline',\n"
"};\n"
"\n"
"var color = {\n"
"transparent: [ 'T' ],\n"
"black: [ 'G', 0 ],\n"
"white: [ 'G', 1 ],\n"
"gray: [ 'G', 0.5 ],\n"
"ltGray: [ 'G', 0.75 ],\n"
"dkGray: [ 'G', 0.25 ],\n"
"red: [ 'RGB', 1, 0, 0 ],\n"
"green: [ 'RGB', 0, 1, 0 ],\n"
"blue: [ 'RGB', 0, 0, 1 ],\n"
"cyan: [ 'CMYK', 1, 0, 0, 0 ],\n"
"magenta: [ 'CMYK', 0, 1, 0, 0 ],\n"
"yellow: [ 'CMYK', 0, 0, 1, 0 ],\n"
"};\n"
"\n"
"color.convert = function (c, colorspace) {\n"
"switch (colorspace) {\n"
"case 'G':\n"
"if (c[0] === 'RGB')\n"
"return [ 'G', c[1] * 0.3 + c[2] * 0.59 + c[3] * 0.11 ];\n"
"if (c[0] === 'CMYK')\n"
"return [ 'CMYK', 1 - Math.min(1, c[1] * 0.3 + c[2] * 0.59 + c[3] * 0.11 + c[4])];\n"
"break;\n"
"case 'RGB':\n"
"if (c[0] === 'G')\n"
"return [ 'RGB', c[1], c[1], c[1] ];\n"
"if (c[0] === 'CMYK')\n"
"return [ 'RGB',\n"
"1 - Math.min(1, c[1] + c[4]),\n"
"1 - Math.min(1, c[2] + c[4]),\n"
"1 - Math.min(1, c[3] + c[4]) ];\n"
"break;\n"
"case 'CMYK':\n"
"if (c[0] === 'G')\n"
"return [ 'CMYK', 0, 0, 0, 1 - c[1] ];\n"
"if (c[0] === 'RGB')\n"
"return [ 'CMYK', 1 - c[1], 1 - c[2], 1 - c[3], 0 ];\n"
"break;\n"
"}\n"
"return c;\n"
"}\n"
"\n"
"color.equal = function (a, b) {\n"
"var i, n\n"
"if (a[0] === 'G')\n"
"a = color.convert(a, b[0]);\n"
"else\n"
"b = color.convert(b, a[0]);\n"
"if (a[0] !== b[0])\n"
"return false;\n"
"switch (a[0]) {\n"
"case 'G': n = 1; break;\n"
"case 'RGB': n = 3; break;\n"
"case 'CMYK': n = 4; break;\n"
"default: n = 0; break;\n"
"}\n"
"for (i = 1; i <= n; ++i)\n"
"if (a[i] !== b[i])\n"
"return false;\n"
"return true;\n"
"}\n"
"\n"
"var font = {\n"
"Cour: 'Courier',\n"
"CourB: 'Courier-Bold',\n"
"CourBI: 'Courier-BoldOblique',\n"
"CourI: 'Courier-Oblique',\n"
"Helv: 'Helvetica',\n"
"HelvB: 'Helvetica-Bold',\n"
"HelvBI: 'Helvetica-BoldOblique',\n"
"HelvI: 'Helvetica-Oblique',\n"
"Symbol: 'Symbol',\n"
"Times: 'Times-Roman',\n"
"TimesB: 'Times-Bold',\n"
"TimesBI: 'Times-BoldItalic',\n"
"TimesI: 'Times-Italic',\n"
"ZapfD: 'ZapfDingbats',\n"
"};\n"
"\n"
"var highlight = {\n"
"i: 'invert',\n"
"n: 'none',\n"
"o: 'outline',\n"
"p: 'push',\n"
"};\n"
"\n"
"var position = {\n"
"textOnly: 0,\n"
"iconOnly: 1,\n"
"iconTextV: 2,\n"
"textIconV: 3,\n"
"iconTextH: 4,\n"
"textIconH: 5,\n"
"overlay: 6,\n"
"};\n"
"\n"
"var scaleHow = {\n"
"proportional: 0,\n"
"anamorphic: 1,\n"
"};\n"
"\n"
"var scaleWhen = {\n"
"always: 0,\n"
"never: 1,\n"
"tooBig: 2,\n"
"tooSmall: 3,\n"
"};\n"
"\n"
"var style = {\n"
"ch: 'check',\n"
"ci: 'circle',\n"
"cr: 'cross',\n"
"di: 'diamond',\n"
"sq: 'square',\n"
"st: 'star',\n"
"};\n"
"\n"
"var zoomtype = {\n"
"fitH: 'FitHeight',\n"
"fitP: 'FitPage',\n"
"fitV: 'FitVisibleWidth',\n"
"fitW: 'FitWidth',\n"
"none: 'NoVary',\n"
"pref: 'Preferred',\n"
"refW: 'ReflowWidth',\n"
"};\n"
"\n"
"util.printd = function (fmt, d) {\n"
"function padZeros(num, places) {\n"
"var s = String(num)\n"
"while (s.length < places)\n"
"s = '0' + s;\n"
"return s;\n"
"}\n"
"if (!(d instanceof Date))\n"
"return null;\n"
"var res = '';\n"
"if (fmt == 0)\n"
"fmt = \"D:yyyymmddHHMMss+00'00'\";\n"
"else if (fmt == 1)\n"
"fmt = \"YYYY.MM.DD HH:MM:ss +00'00'\";\n"
"else if (fmt == 2)\n"
"fmt = \"YYYY/MM/DD HH:MM:ss\";\n"
"var tokens = fmt.match(/(\\\\.|m+|d+|y+|H+|h+|M+|s+|t+|[^\\\\mdyHhMst]+)/g);\n"
"var length = tokens ? tokens.length : 0;\n"
"var tok, i;\n"
"for (i = 0; i < length; ++i) {\n"
"tok = tokens[i];\n"
"switch (tok)\n"
"{\n"
"default:\n"
"if (tok[0] == '\\\\')\n"
"res += tok[1];\n"
"else\n"
"res += tok;\n"
"break;\n"
"case 'mmmm': res += MuPDF.monthName[d.getMonth()]; break;\n"
"case 'mmm': res += MuPDF.monthName[d.getMonth()].substring(0, 3); break;\n"
"case 'mm': res += padZeros(d.getMonth()+1, 2); break;\n"
"case 'm': res += d.getMonth()+1; break;\n"
"case 'dddd': res += MuPDF.dayName[d.getDay()]; break;\n"
"case 'ddd': res += MuPDF.dayName[d.getDay()].substring(0, 3); break;\n"
"case 'dd': res += padZeros(d.getDate(), 2); break;\n"
"case 'd': res += d.getDate(); break;\n"
"case 'yyyy': res += d.getFullYear(); break;\n"
"case 'yy': res += d.getFullYear()%100; break;\n"
"case 'HH': res += padZeros(d.getHours(), 2); break;\n"
"case 'H': res += d.getHours(); break;\n"
"case 'hh': res += padZeros((d.getHours()+11)%12+1, 2); break;\n"
"case 'h': res += (d.getHours()+11)%12+1; break;\n"
"case 'MM': res += padZeros(d.getMinutes(), 2); break;\n"
"case 'M': res += d.getMinutes(); break;\n"
"case 'ss': res += padZeros(d.getSeconds(), 2); break;\n"
"case 's': res += d.getSeconds(); break;\n"
"case 'tt': res += d.getHours() < 12 ? 'am' : 'pm'; break;\n"
"case 't': res += d.getHours() < 12 ? 'a' : 'p'; break;\n"
"}\n"
"}\n"
"return res;\n"
"}\n"
"\n"
"util.printx = function (fmt, val) {\n"
"function toUpper(str) { return str.toUpperCase(); }\n"
"function toLower(str) { return str.toLowerCase(); }\n"
"function toSame(str) { return str; }\n"
"var convertCase = toSame;\n"
"var res = '';\n"
"var i, m;\n"
"var n = fmt ? fmt.length : 0;\n"
"for (i = 0; i < n; ++i) {\n"
"switch (fmt.charAt(i)) {\n"
"case '\\\\':\n"
"if (++i < n)\n"
"res += fmt.charAt(i);\n"
"break;\n"
"case 'X':\n"
"m = val.match(/\\w/);\n"
"if (m) {\n"
"res += convertCase(m[0]);\n"
"val = val.replace(/^\\W*\\w/, '');\n"
"}\n"
"break;\n"
"case 'A':\n"
"m = val.match(/[A-Za-z]/);\n"
"if (m) {\n"
"res += convertCase(m[0]);\n"
"val = val.replace(/^[^A-Za-z]*[A-Za-z]/, '');\n"
"}\n"
"break;\n"
"case '9':\n"
"m = val.match(/\\d/);\n"
"if (m) {\n"
"res += m[0];\n"
"val = val.replace(/^\\D*\\d/, '');\n"
"}\n"
"break;\n"
"case '*':\n"
"res += convertCase(val);\n"
"val = '';\n"
"break;\n"
"case '?':\n"
"if (val !== '') {\n"
"res += convertCase(val.charAt(0));\n"
"val = val.substring(1);\n"
"}\n"
"break;\n"
"case '=':\n"
"convertCase = toSame;\n"
"break;\n"
"case '>':\n"
"convertCase = toUpper;\n"
"break;\n"
"case '<':\n"
"convertCase = toLower;\n"
"break;\n"
"default:\n"
"res += convertCase(fmt.charAt(i));\n"
"break;\n"
"}\n"
"}\n"
"return res;\n"
"}\n"
"\n"
"function AFMergeChange(event) {\n"
"var prefix, postfix;\n"
"var value = event.value;\n"
"if (event.willCommit)\n"
"return value;\n"
"if (event.selStart >= 0)\n"
"prefix = value.substring(0, event.selStart);\n"
"else\n"
"prefix = '';\n"
"if (event.selEnd >= 0 && event.selEnd <= value.length)\n"
"postfix = value.substring(event.selEnd, value.length);\n"
"else\n"
"postfix = '';\n"
"return prefix + event.change + postfix;\n"
"}\n"
"\n"
"function AFExtractNums(string) {\n"
"if (string.charAt(0) == '.' || string.charAt(0) == ',')\n"
"string = '0' + string;\n"
"return string.match(/\\d+/g);\n"
"}\n"
"\n"
"function AFMakeNumber(string) {\n"
"if (typeof string == 'number')\n"
"return string;\n"
"if (typeof string != 'string')\n"
"return null;\n"
"var nums = AFExtractNums(string);\n"
"if (!nums)\n"
"return null;\n"
"var result = nums.join('.');\n"
"if (string.indexOf('-.') >= 0)\n"
"result = '0.' + result;\n"
"if (string.indexOf('-') >= 0)\n"
"return -result;\n"
"return result;\n"
"}\n"
"\n"
"function AFExtractTime(dt) {\n"
"var ampm = dt.match(/(am|pm)/);\n"
"dt = dt.replace(/(am|pm)/, '');\n"
"var t = dt.match(/\\d{1,2}:\\d{1,2}:\\d{1,2}/);\n"
"dt = dt.replace(/\\d{1,2}:\\d{1,2}:\\d{1,2}/, '');\n"
"if (!t) {\n"
"t = dt.match(/\\d{1,2}:\\d{1,2}/);\n"
"dt = dt.replace(/\\d{1,2}:\\d{1,2}/, '');\n"
"}\n"
"return [dt, t?t[0]+(ampm?ampm[0]:''):''];\n"
"}\n"
"\n"
"function AFParseDateOrder(fmt) {\n"
"var i;\n"
"var order = '';\n"
"\n"
"\n"
"fmt += 'mdy';\n"
"\n"
"for (i = 0; i < fmt.length; i++) {\n"
"var c = fmt.charAt(i);\n"
"if ('ymd'.indexOf(c) !== -1 && order.indexOf(c) === -1)\n"
"order += c;\n"
"}\n"
"\n"
"return order;\n"
"}\n"
"\n"
"function AFMatchMonth(d) {\n"
"var m = d.match(MuPDF.monthPattern);\n"
"return m ? MuPDF.shortMonthName.indexOf(m[0].toLowerCase()) : null;\n"
"}\n"
"\n"
"function AFParseTime(str, d) {\n"
"if (!str)\n"
"return d;\n"
"\n"
"if (!d)\n"
"d = new Date();\n"
"\n"
"var ampm = str.match(/(am|pm)/);\n"
"var nums = str.match(/\\d+/g);\n"
"var hour, min, sec;\n"
"\n"
"if (!nums)\n"
"return null;\n"
"\n"
"sec = 0;\n"
"\n"
"switch (nums.length) {\n"
"case 3:\n"
"sec = parseInt(nums[2]);\n"
"case 2:\n"
"hour = parseInt(nums[0]);\n"
"min = parseInt(nums[1]);\n"
"break;\n"
"default:\n"
"return null;\n"
"}\n"
"\n"
"ampm = ampm && ampm[0]\n"
"\n"
"if (ampm === 'am' && hour < 12)\n"
"hour = 12 + hour;\n"
"if (ampm === 'pm' && hour >= 12)\n"
"hour = 0 + hour - 12;\n"
"\n"
"d.setHours(hour, min, sec);\n"
"\n"
"if (d.getHours() !== hour || d.getMinutes() !== min || d.getSeconds() !== sec)\n"
"return null;\n"
"\n"
"return d;\n"
"}\n"
"\n"
"function AFParseDateEx(d, fmt) {\n"
"var i;\n"
"var dt = AFExtractTime(d);\n"
"var nums = dt[0].match(/\\d+/g);\n"
"var order = AFParseDateOrder(fmt);\n"
"var text_month = AFMatchMonth(dt[0]);\n"
"var dout = new Date();\n"
"var year = dout.getFullYear();\n"
"var month = dout.getMonth();\n"
"var date = dout.getDate();\n"
"\n"
"dout.setHours(12, 0, 0);\n"
"\n"
"if (!nums)\n"
"return null;\n"
"\n"
"if (nums.length == 1 && nums[0].length == fmt.length && !text_month) {\n"
"\n"
"\n"
"var num = nums[0];\n"
"nums = [''];\n"
"for (i = 0; i < fmt.length; i++)\n"
"{\n"
"nums[nums.length-1] += num.charAt(i);\n"
"if (i+1 < fmt.length && fmt.charAt(i) != fmt.charAt(i+1))\n"
"nums.push('');\n"
"}\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
"var total = nums.length + (text_month ? 1 : 0);\n"
"\n"
"if (total < 2 || nums.length > 3)\n"
"return null;\n"
"\n"
"if (nums.length < 3 && text_month) {\n"
"\n"
"month = text_month;\n"
"order = order.replace('m', '');\n"
"}\n"
"\n"
"order = order.substring(0, nums.length);\n"
"\n"
"\n"
"if (order === 'ym' || order === 'my' || (order === 'y' && text_month))\n"
"date = 1;\n"
"\n"
"for (i = 0; i < nums.length; i++) {\n"
"switch (order.charAt(i)) {\n"
"case 'y': year = parseInt(nums[i]); break;\n"
"case 'm': month = parseInt(nums[i]) - 1; break;\n"
"case 'd': date = parseInt(nums[i]); break;\n"
"}\n"
"}\n"
"\n"
"if (year < 100) {\n"
"if (fmt.search('yyyy') !== -1)\n"
"return null;\n"
"if (year >= 50)\n"
"year = 1900 + year;\n"
"else if (year >= 0)\n"
"year = 2000 + year;\n"
"}\n"
"\n"
"dout.setFullYear(year, month, date);\n"
"\n"
"if (dout.getFullYear() !== year || dout.getMonth() !== month || dout.getDate() !== date)\n"
"return null;\n"
"\n"
"return AFParseTime(dt[1], dout);\n"
"}\n"
"\n"
"function AFDate_KeystrokeEx(fmt) {\n"
"if (event.willCommit && !AFParseDateEx(event.value, fmt)) {\n"
"app.alert('The date/time entered ('+event.value+') does not match the format ('+fmt+') of the field [ '+event.target.name+' ]');\n"
"event.rc = false;\n"
"}\n"
"}\n"
"\n"
"function AFDate_Keystroke(index) {\n"
"AFDate_KeystrokeEx(MuPDF.dateFormats[index]);\n"
"}\n"
"\n"
"function AFDate_FormatEx(fmt) {\n"
"var d = AFParseDateEx(event.value, fmt);\n"
"event.value = d ? util.printd(fmt, d) : '';\n"
"}\n"
"\n"
"function AFDate_Format(index) {\n"
"AFDate_FormatEx(MuPDF.dateFormats[index]);\n"
"}\n"
"\n"
"function AFTime_Keystroke(index) {\n"
"if (event.willCommit && !AFParseTime(event.value, null)) {\n"
"app.alert('The value entered ('+event.value+') does not match the format of the field [ '+event.target.name+' ]');\n"
"event.rc = false;\n"
"}\n"
"}\n"
"\n"
"function AFTime_FormatEx(fmt) {\n"
"var d = AFParseTime(event.value, null);\n"
"event.value = d ? util.printd(fmt, d) : '';\n"
"}\n"
"\n"
"function AFTime_Format(index) {\n"
"AFTime_FormatEx(MuPDF.timeFormats[index]);\n"
"}\n"
"\n"
"function AFSpecial_KeystrokeEx(fmt) {\n"
"function toUpper(str) { return str.toUpperCase(); }\n"
"function toLower(str) { return str.toLowerCase(); }\n"
"function toSame(str) { return str; }\n"
"var convertCase = toSame;\n"
"var val = event.value;\n"
"var res = '';\n"
"var i = 0;\n"
"var m;\n"
"var length = fmt ? fmt.length : 0;\n"
"while (i < length) {\n"
"switch (fmt.charAt(i)) {\n"
"case '\\\\':\n"
"i++;\n"
"if (i >= length)\n"
"break;\n"
"res += fmt.charAt(i);\n"
"if (val && val.charAt(0) === fmt.charAt(i))\n"
"val = val.substring(1);\n"
"break;\n"
"\n"
"case 'X':\n"
"m = val.match(/^\\w/);\n"
"if (!m) {\n"
"event.rc = false;\n"
"break;\n"
"}\n"
"res += convertCase(m[0]);\n"
"val = val.substring(1);\n"
"break;\n"
"\n"
"case 'A':\n"
"m = val.match(/^[A-Za-z]/);\n"
"if (!m) {\n"
"event.rc = false;\n"
"break;\n"
"}\n"
"res += convertCase(m[0]);\n"
"val = val.substring(1);\n"
"break;\n"
"\n"
"case '9':\n"
"m = val.match(/^\\d/);\n"
"if (!m) {\n"
"event.rc = false;\n"
"break;\n"
"}\n"
"res += m[0];\n"
"val = val.substring(1);\n"
"break;\n"
"\n"
"case '*':\n"
"res += convertCase(val);\n"
"val = '';\n"
"break;\n"
"\n"
"case '?':\n"
"if (val === '') {\n"
"event.rc = false;\n"
"break;\n"
"}\n"
"res += convertCase(val.charAt(0));\n"
"val = val.substring(1);\n"
"break;\n"
"\n"
"case '=':\n"
"convertCase = toSame;\n"
"break;\n"
"case '>':\n"
"convertCase = toUpper;\n"
"break;\n"
"case '<':\n"
"convertCase = toLower;\n"
"break;\n"
"\n"
"default:\n"
"res += fmt.charAt(i);\n"
"if (val && val.charAt(0) === fmt.charAt(i))\n"
"val = val.substring(1);\n"
"break;\n"
"}\n"
"\n"
"i++;\n"
"}\n"
"\n"
"\n"
"if (val.length > 0)\n"
"event.rc = false;\n"
"\n"
"if (event.rc)\n"
"event.value = res;\n"
"else if (event.willCommit)\n"
"app.alert('The value entered ('+event.value+') does not match the format of the field [ '+event.target.name+' ] should be '+fmt);\n"
"}\n"
"\n"
"function AFSpecial_Keystroke(index) {\n"
"if (event.willCommit) {\n"
"switch (index) {\n"
"case 0:\n"
"if (!event.value.match(/^\\d{5}$/))\n"
"event.rc = false;\n"
"break;\n"
"case 1:\n"
"if (!event.value.match(/^\\d{5}[-. ]?\\d{4}$/))\n"
"event.rc = false;\n"
"break;\n"
"case 2:\n"
"if (!event.value.match(/^((\\(\\d{3}\\)|\\d{3})[-. ]?)?\\d{3}[-. ]?\\d{4}$/))\n"
"event.rc = false;\n"
"break;\n"
"case 3:\n"
"if (!event.value.match(/^\\d{3}[-. ]?\\d{2}[-. ]?\\d{4}$/))\n"
"event.rc = false;\n"
"break;\n"
"}\n"
"if (!event.rc)\n"
"app.alert('The value entered ('+event.value+') does not match the format of the field [ '+event.target.name+' ]');\n"
"}\n"
"}\n"
"\n"
"function AFSpecial_Format(index) {\n"
"var res;\n"
"switch (index) {\n"
"case 0:\n"
"res = util.printx('99999', event.value);\n"
"break;\n"
"case 1:\n"
"res = util.printx('99999-9999', event.value);\n"
"break;\n"
"case 2:\n"
"res = util.printx('9999999999', event.value);\n"
"res = util.printx(res.length >= 10 ? '(999) 999-9999' : '999-9999', event.value);\n"
"break;\n"
"case 3:\n"
"res = util.printx('999-99-9999', event.value);\n"
"break;\n"
"}\n"
"event.value = res ? res : '';\n"
"}\n"
"\n"
"function AFNumber_Keystroke(nDec, sepStyle, negStyle, currStyle, strCurrency, bCurrencyPrepend) {\n"
"if (sepStyle & 2) {\n"
"if (!event.value.match(/^[+-]?\\d*[,.]?\\d*$/))\n"
"event.rc = false;\n"
"} else {\n"
"if (!event.value.match(/^[+-]?\\d*\\.?\\d*$/))\n"
"event.rc = false;\n"
"}\n"
"if (event.willCommit) {\n"
"if (!event.value.match(/\\d/))\n"
"event.rc = false;\n"
"if (!event.rc)\n"
"app.alert('The value entered ('+event.value+') does not match the format of the field [ '+event.target.name+' ]');\n"
"}\n"
"}\n"
"\n"
"function AFNumber_Format(nDec, sepStyle, negStyle, currStyle, strCurrency, bCurrencyPrepend) {\n"
"var value = AFMakeNumber(event.value);\n"
"var fmt = '%,' + sepStyle + '.' + nDec + 'f';\n"
"if (value == null) {\n"
"event.value = '';\n"
"return;\n"
"}\n"
"if (bCurrencyPrepend)\n"
"fmt = strCurrency + fmt;\n"
"else\n"
"fmt = fmt + strCurrency;\n"
"if (value < 0) {\n"
"/* negStyle: 0=MinusBlack, 1=Red, 2=ParensBlack, 3=ParensRed */\n"
"value = Math.abs(value);\n"
"if (negStyle == 2 || negStyle == 3)\n"
"fmt = '(' + fmt + ')';\n"
"else if (negStyle == 0)\n"
"fmt = '-' + fmt;\n"
"if (negStyle == 1 || negStyle == 3)\n"
"event.target.textColor = color.red;\n"
"else\n"
"event.target.textColor = color.black;\n"
"} else {\n"
"event.target.textColor = color.black;\n"
"}\n"
"event.value = util.printf(fmt, value);\n"
"}\n"
"\n"
"function AFPercent_Keystroke(nDec, sepStyle) {\n"
"AFNumber_Keystroke(nDec, sepStyle, 0, 0, '', true);\n"
"}\n"
"\n"
"function AFPercent_Format(nDec, sepStyle) {\n"
"var val = AFMakeNumber(event.value);\n"
"if (val == null) {\n"
"event.value = '';\n"
"return;\n"
"}\n"
"event.value = (val * 100) + '';\n"
"AFNumber_Format(nDec, sepStyle, 0, 0, '%', false);\n"
"}\n"
"\n"
"function AFSimple_Calculate(op, list) {\n"
"var i, res;\n"
"\n"
"switch (op) {\n"
"case 'SUM': res = 0; break;\n"
"case 'PRD': res = 1; break;\n"
"case 'AVG': res = 0; break;\n"
"}\n"
"\n"
"if (typeof list === 'string')\n"
"list = list.split(/ *, */);\n"
"\n"
"for (i = 0; i < list.length; i++) {\n"
"var field = this.getField(list[i]);\n"
"var value = Number(field.value);\n"
"switch (op) {\n"
"case 'SUM': res += value; break;\n"
"case 'PRD': res *= value; break;\n"
"case 'AVG': res += value; break;\n"
"case 'MIN': if (i === 0 || value < res) res = value; break;\n"
"case 'MAX': if (i === 0 || value > res) res = value; break;\n"
"}\n"
"}\n"
"\n"
"if (op === 'AVG')\n"
"res /= list.length;\n"
"\n"
"event.value = res;\n"
"}\n"
"\n"
"function AFRange_Validate(lowerCheck, lowerLimit, upperCheck, upperLimit) {\n"
"if (upperCheck && event.value > upperLimit)\n"
"event.rc = false;\n"
"if (lowerCheck && event.value < lowerLimit)\n"
"event.rc = false;\n"
"if (!event.rc) {\n"
"if (lowerCheck && upperCheck)\n"
"app.alert(util.printf('The entered value ('+event.value+') must be greater than or equal to %s and less than or equal to %s', lowerLimit, upperLimit));\n"
"else if (lowerCheck)\n"
"app.alert(util.printf('The entered value ('+event.value+') must be greater than or equal to %s', lowerLimit));\n"
"else\n"
"app.alert(util.printf('The entered value ('+event.value+') must be less than or equal to %s', upperLimit));\n"
"}\n"
"}\n"
"\n"
"/* Compatibility ECMAScript functions */\n"
"String.prototype.substr = function (start, length) {\n"
"if (start < 0)\n"
"start = this.length + start;\n"
"if (length === undefined)\n"
"return this.substring(start, this.length);\n"
"return this.substring(start, start + length);\n"
"}\n"
"Date.prototype.getYear = Date.prototype.getFullYear;\n"
"Date.prototype.setYear = Date.prototype.setFullYear;\n"
"Date.prototype.toGMTString = Date.prototype.toUTCString;\n"
"\n"
"console.clear = function() { console.println('--- clear console ---\\n'); };\n"
"console.show = function(){};\n"
"console.hide = function(){};\n"
"\n"
"app.plugIns = [];\n"
"app.viewerType = 'Reader';\n"
"app.language = 'ENU';\n"
"app.viewerVersion = NaN;\n"
"app.execDialog = function () { return 'cancel'; }\n"
