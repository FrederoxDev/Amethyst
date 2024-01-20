const fs = window.require('fs') as typeof import('fs');
import { WriteStream } from "fs";

import CancellationToken from "./CancellationToken";
import { ActionComplete, DownloadProgress } from "./Progress";

export class Downloader {
  static async downloadFile(from: string, to: string, cancellationToken: CancellationToken, onProgress: DownloadProgress = () => {}, onComplete: ActionComplete = () => {}) {
    const response = await fetch(from);
    if (!response.ok) {
      throw new Error('Download error.');
    }

    const inStream = response.body;
    const maxLength = parseInt(response.headers.get('Content-Length') || '0', 10);
    if (inStream) {
      const stream = inStream.getReader();
      const outStream: WriteStream = fs.createWriteStream(to);
      let downloadProgress = 0;
      try {
        while (true) {
          const { done, value } = await stream.read();
          if (done || cancellationToken.isCancellationRequested())
            break;
          downloadProgress += value.length;
          onProgress(downloadProgress, maxLength);
          if (outStream) {
            outStream.write(value);
          }
        }
      }
      finally {
        if (cancellationToken.isCancellationRequested()) {
          console.log('downloadFile cancelled.');
          fs.unlinkSync(to);
        }
        stream.releaseLock();
        onComplete(true);
      }
    }
  }
}